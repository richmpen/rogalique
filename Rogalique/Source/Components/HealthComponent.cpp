#include "HealthComponent.h"

#include "GameObject.h"
#include "GameWorld.h"

namespace Rogalique {

HealthComponent::HealthComponent(EngineCore::GameObject* gameObject)
    : Component(gameObject) {}

void HealthComponent::Update(float deltaTime) {}

void HealthComponent::Render() {}

void HealthComponent::TakeDamage(int damageValue) {
    SetHealth(GetHealth() - damageValue);
    LOG_INFO(gameObject->GetName()
             << ": Get damage " << damageValue << ", Current health "
             << std::to_string(GetHealth()));

    if (health <= 0) {
        Die();
    }
}

void HealthComponent::SetHealth(int health) { this->health = health; }

int HealthComponent::GetHealth() { return this->health; }

void HealthComponent::Die() {
    LOG_INFO(gameObject->GetName() << ": Die");
    EngineCore::GameWorld::Instance()->DestroyGameObject(this->gameObject);
}

}  // namespace Rogalique