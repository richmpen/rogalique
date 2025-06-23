#pragma once
#include "Component.h"

namespace Rogalique {

class HealthComponent : public EngineCore::Component {
   public:
    HealthComponent(EngineCore::GameObject* gameObject);
    void TakeDamage(int damageValue);
    void SetHealth(int health);
    int GetHealth();
    void Die();
    void Update(float deltaTime) override;
    void Render() override;

   private:
    int health = 0;
};

}  // namespace Rogalique
