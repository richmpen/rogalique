#include "FightComponent.h"

#include "EnemyAIComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"

namespace Rogalique {
FightComponent::FightComponent(EngineCore::GameObject* gameObject)
    : Component(gameObject) {
    collider = gameObject->GetComponent<EngineCore::SpriteColliderComponent>();
    renderer = gameObject->GetComponent<EngineCore::SpriteRendererComponent>();

    if (collider == nullptr) {
        LOG_ERROR("FightComponent required to SpriteColliderComponent.");
        gameObject->RemoveComponent(this);
        return;
    }

    collider->SubscribeCollision([this](EngineCore::Collision collision) {
        if (health <= 0 || attackCooldown > 0.0f) return;

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
            otherFight->TakeDamage(this->damage);
            attackCooldown = 1.0f;
            flashTimer = 2.0f;

            // If it's a creeper and collides with a player, trigger an
            // explosion
            if (this->gameObject->GetName() == "Creeper" &&
                otherObject->GetName() == "Player") {
                StartCreeperExplosion();
            }
        }
    });
}

void FightComponent::StartCreeperExplosion() {
    isCreeperExploding = true;
    explosionTimer = 2.0f;  // 2 seconds to death
    if (renderer) {
        renderer->SetTexture(
            *EngineCore::ResourceSystem::Instance()->GetTextureShared(
                "creeperExplosion"));
    }
    auto aiComponent = gameObject->GetComponent<EnemyAIComponent>();
    auto rigidbody = gameObject->GetComponent<EngineCore::RigidbodyComponent>();
    if (aiComponent) {
        aiComponent->SetMoveSpeed(0.0f);
        rigidbody->SetKinematic(true);
        gameObject->RemoveComponent(collider);
    }
}

void FightComponent::Update(float deltaTime) {
    if (isCreeperExploding) {
        explosionTimer -= deltaTime;
        if (explosionTimer <= 0.0f) {
            Die();
        }
    } else if (flashTimer > 0.0f) {
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

void FightComponent::TakeDamage(int damageValue) {
    SetHealth(GetHealth() - damageValue);
    LOG_INFO(gameObject->GetName()
             << ": Get damage " << damageValue << ", Current health "
             << std::to_string(GetHealth()));

    if (health <= 0) {
        Die();
    }
}

void FightComponent::Die() {
    LOG_INFO(gameObject->GetName() << ": Die");
    EngineCore::GameWorld::Instance()->DestroyGameObject(this->gameObject);
}

void FightComponent::SetDamage(int damage) { this->damage = damage; }

int FightComponent::GetDamage() { return this->damage; }

void FightComponent::SetHealth(int health) { this->health = health; }

int FightComponent::GetHealth() { return this->health; }

void FightComponent::SetTargetType(TargetType type) { this->targetType = type; }

TargetType FightComponent::GetTargetType() const { return targetType; }

void FightComponent::Render() {}

}  // namespace EngineCore