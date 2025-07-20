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
}

void ArmorComponent::SetArmor(int newArmor) { this->armor = newArmor; }

void ArmorComponent::AddArmor(int count) {
    this->armor = std::min(this->armor + count, this->maxArmor);
}

int ArmorComponent::GetArmor() const { return this->armor; }

void ArmorComponent::SetMaxArmor(int newMaxArmor) {
    this->maxArmor = newMaxArmor;
}

int ArmorComponent::GetMaxArmor() const { return this->maxArmor; }

}  // namespace Rogalique