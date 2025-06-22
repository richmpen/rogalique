#include "FightComponent.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
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
            (collision.GetFirst() == collider)
                                               ? collision.GetSecond()
                                               : collision.GetFirst();

        EngineCore::GameObject* otherObject = otherCollider->GetGameObject();

        FightComponent* otherFight =
            otherObject->GetComponent<FightComponent>();

        if (otherFight &&
            otherFight->GetTargetType() != this->GetTargetType() &&
            otherFight->GetTargetType() != TargetType::None &&
            this->GetTargetType() != TargetType::None) {
            otherFight->healthComponent->TakeDamage(this->damage);
            attackCooldown = 1.0f;
            flashTimer = 2.0f;

            // If it's a creeper and collides with a player, trigger an
            // explosion
            if (this->gameObject->GetComponent<CreeperExplosion>() != 0 &&
                otherObject->GetComponent<EngineCore::InputComponent>() != 0) {
                creeperExplosion->StartCreeperExplosion();
            }
        }
    });
}



void FightComponent::Update(float deltaTime) {
    
    if (flashTimer > 0.0f && gameObject->GetComponent<CreeperExplosion>() == 0) {
        flashTimer -= deltaTime;
        attackCooldown = flashTimer;
    
        if (renderer) {
            renderer->SetColor(sf::Color(255, 0, 0));
        }
    } else {
        attackCooldown = 0.0f;
    
        if (renderer) {
            renderer->SetColor(sf::Color(255, 255, 255));
        }
    }
}



void FightComponent::SetDamage(int damage) { this->damage = damage; }

int FightComponent::GetDamage() { return this->damage; }

void FightComponent::SetTargetType(TargetType type) { this->targetType = type; }

TargetType FightComponent::GetTargetType() const { return targetType; }

void FightComponent::Render() {}

}  // namespace EngineCore