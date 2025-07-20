#pragma once
#include "ArmorComponent.h"
#include "Component.h"

namespace Rogalique {

class HealthComponent : public EngineCore::Component {
   public:
    HealthComponent(EngineCore::GameObject* gameObject);
    void TakeDamage(int damageValue);
    void SetHealth(int health);
    int GetHealth() const;
    void SetMaxHealth(int newMaxHealth);
    int GetMaxHealth() const;
    void AddHealth(int healCount);
    void Die() const;
    void Update(float deltaTime) override;
    void Render() override;

   private:
    int health = 0;
    int maxHealth = 0;
};

}  // namespace Rogalique
