#include "FightComponent.h"

#include "GameObject.h"
#include "GameSettings.h"
#include "GameWorld.h"
#include "InputComponent.h"
#include "ResourceSystem.h"

namespace Rogalique {
FightComponent::FightComponent(EngineCore::GameObject* gameObject)
    : Component(gameObject) {
    creeperExplosion = gameObject->GetComponent<CreeperExplosion>();
    healthComponent = gameObject->GetComponent<HealthComponent>();
    collider = gameObject->GetComponent<EngineCore::SpriteColliderComponent>();
    renderer = gameObject->GetComponent<EngineCore::SpriteRendererComponent>();

    if (collider == nullptr) {
        LOG_ERROR("FightComponent required to SpriteColliderComponent.");
        gameObject->RemoveComponent(this);
        return;
    }
    if (healthComponent == nullptr) {
        LOG_ERROR("FightComponent required to HealthComponent.");
        gameObject->RemoveComponent(this);
        return;
    }
    if (creeperExplosion == nullptr) {
        LOG_INFO("FightComponent: CreeperExplosion not present. This is fine.");
    }

    collider->SubscribeCollision([this](EngineCore::Collision collision) {
        if (healthComponent->GetHealth() <= 0 || attackCooldown > 0.0f) return;

        EngineCore::ColliderComponent* otherCollider =
            (collision.GetFirst() == collider) ? collision.GetSecond()
                                               : collision.GetFirst();

        EngineCore::GameObject* otherObject = otherCollider->GetGameObject();

        FightComponent* otherFight =
            otherObject->GetComponent<FightComponent>();

        if (otherFight &&
            otherFight->GetTargetType() != this->GetTargetType() &&
            otherFight->GetTargetType() != TargetType::None &&
            this->GetTargetType() != TargetType::None) {
            otherFight->healthComponent->TakeDamage(this->damage);
            attackCooldown = SETTINGS.ATTACK_COOLDOWN_DURATION;
            flashTimer = SETTINGS.DAMAGE_FLASH_TIMER;

            if (this->gameObject->GetComponent<CreeperExplosion>() != nullptr &&
                otherObject->GetComponent<EngineCore::InputComponent>() !=
                    nullptr) {
                creeperExplosion->StartCreeperExplosion();
            }
        }
    });
}

void FightComponent::Update(float deltaTime) {
    if (flashTimer > 0.0f &&
        gameObject->GetComponent<CreeperExplosion>() == nullptr) {
        flashTimer -= deltaTime;
        if (renderer && flashTimer > 0.0f) {
            renderer->SetColor(sf::Color(255, 0, 0));
        } else if (renderer) {
            renderer->SetColor(sf::Color(255, 255, 255));
        }
    } else if (renderer) {
        renderer->SetColor(sf::Color(255, 255, 255));
    }

    if (attackCooldown > 0.0f) {
        attackCooldown -= deltaTime;
    }
}

void FightComponent::SetDamage(int damage) { this->damage = damage; }
int FightComponent::GetDamage() const { return this->damage; }
void FightComponent::SetTargetType(TargetType type) { this->targetType = type; }
TargetType FightComponent::GetTargetType() const { return targetType; }
void FightComponent::Render() {}

}  // namespace Rogalique