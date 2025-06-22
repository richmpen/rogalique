#pragma once
#include "Component.h"
#include "CreeperExplosion.h"
#include "HealthComponent.h"
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

    void SetDamage(int damage);
    int GetDamage();

    void SetTargetType(TargetType type);
    TargetType GetTargetType() const;

   private:
    int damage = 0;
    TargetType targetType = TargetType::None;

    float flashTimer = 0.0f;
    float attackCooldown = 0.0f;
    

    HealthComponent* healthComponent;
    EngineCore::SpriteColliderComponent* collider;
    EngineCore::SpriteRendererComponent* renderer;
    CreeperExplosion* creeperExplosion;
};

}  // namespace EngineCore