#pragma once
#include "Component.h"
#include "RigidbodyComponent.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"

#include <SFML/Graphics.hpp>

namespace Rogalique {

enum class TargetType {
    Player = 0,
    Enemy,
    None,
};

class FightComponent : public EngineCore::Component {
   public:
    FightComponent(EngineCore::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    void TakeDamage(int amount);
    void Die();

    void SetDamage(int damage);
    int GetDamage();

    void SetHealth(int health);
    int GetHealth();

    void SetTargetType(TargetType type);
    TargetType GetTargetType() const;

    void StartCreeperExplosion();

   private:
    int damage = 0;
    int health = 0;
    TargetType targetType = TargetType::None;

    float flashTimer = 0.0f;
    float attackCooldown = 0.0f;
    float explosionTimer = 0.0f;
    bool isCreeperExploding = false;

    EngineCore::SpriteColliderComponent* collider;
    EngineCore::SpriteRendererComponent* renderer;
};

}  // namespace EngineCore