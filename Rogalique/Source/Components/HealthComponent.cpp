#include "HealthComponent.h"

#include "ArmorComponent.h"
#include "GameObject.h"
#include "GameWorld.h"

namespace Rogalique {

HealthComponent::HealthComponent(EngineCore::GameObject* gameObject)
    : Component(gameObject) {}

void HealthComponent::Update(float deltaTime) {}

void HealthComponent::Render() {}

void HealthComponent::TakeDamage(int damageValue) {
    if (gameObject->GetComponent<ArmorComponent>() != 0) {
        auto armor = gameObject->GetComponent<ArmorComponent>();
        if (armor->GetArmor() <= 0) {
            SetHealth(GetHealth() - damageValue);
        } else {
            armor->TakeDamage(damageValue);
        }
    } else {
        SetHealth(GetHealth() - damageValue);
    }
    if (health <= 0) {
        Die();
    }
}

void HealthComponent::SetHealth(int newHealth) { this->health = newHealth; }

int HealthComponent::GetHealth() const { return this->health; }

void HealthComponent::SetMaxHealth(int newMaxHealth) {
    this->maxHealth = newMaxHealth;
}

int HealthComponent::GetMaxHealth() const { return this->maxHealth; }

void HealthComponent::AddHealth(int count) {
    this->health = std::min(this->health + count, this->maxHealth);
}

void HealthComponent::Die() const {
    EngineCore::GameWorld::Instance()->DestroyGameObject(this->gameObject);
}

}  // namespace Rogalique