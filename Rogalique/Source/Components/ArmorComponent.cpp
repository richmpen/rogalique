#include "ArmorComponent.h"

#include "GameObject.h"
#include "GameWorld.h"

namespace Rogalique {

ArmorComponent::ArmorComponent(EngineCore::GameObject* gameObject)
    : Component(gameObject) {}

void ArmorComponent::Update(float deltaTime) {}

void ArmorComponent::Render() {}

void ArmorComponent::TakeDamage(int damageValue) {
    SetArmor(GetArmor() - damageValue);
    LOG_INFO(gameObject->GetName()
             << ": Get damage " << damageValue << ", Current armor "
             << std::to_string(GetArmor()))
}

void ArmorComponent::SetArmor(int newArmor) { this->armor = newArmor; }

int ArmorComponent::GetArmor() const { return this->armor; }

void ArmorComponent::SetMaxArmor(int newMaxArmor) {
    this->maxArmor = newMaxArmor;
}

int ArmorComponent::GetMaxArmor() const { return this->maxArmor; }

}  // namespace Rogalique