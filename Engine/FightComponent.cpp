#include "pch.h"

#include "FightComponent.h"

#include "GameObject.h"
#include "GameWorld.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"

namespace EngineCore {
FightComponent::FightComponent(GameObject* gameObject) : Component(gameObject) {
    collider = gameObject->GetComponent<SpriteColliderComponent>();
    renderer = gameObject->GetComponent<SpriteRendererComponent>();

    if (collider == nullptr) {
        LOG_ERROR("FightComponent required to SpriteColliderComponent.");
        gameObject->RemoveComponent(this);
        return;
    }

    collider->SubscribeCollision([this](Collision collision) {
        if (health <= 0 || attackCooldown > 0.0f) return;

        ColliderComponent* otherCollider = (collision.GetFirst() == collider)
                                               ? collision.GetSecond()
                                               : collision.GetFirst();

        GameObject* otherObject = otherCollider->GetGameObject();

        FightComponent* otherFight =
            otherObject->GetComponent<FightComponent>();

        if (otherFight &&
            otherFight->GetTargetType() != this->GetTargetType() &&
            otherFight->GetTargetType() != EnemyType::None &&
            this->GetTargetType() != EnemyType::None) {
            otherFight->TakeDamage(this->damage);
            attackCooldown = 1.0f;
            flashTimer = 1.0f;
        }
    });
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
    GameWorld::Instance()->DestroyGameObject(this->gameObject);
}

void FightComponent::SetDamage(int damage) { this->damage = damage; }

int FightComponent::GetDamage() { return this->damage; }

void FightComponent::SetHealth(int health) { this->health = health; }

int FightComponent::GetHealth() { return this->health; }

void FightComponent::SetTargetType(EnemyType type) { this->targetType = type; }

EnemyType FightComponent::GetTargetType() const { return targetType; }

void FightComponent::Update(float deltaTime) {
    if (flashTimer > 0.0f) {
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

void FightComponent::Render() {}
}  // namespace EngineCore
