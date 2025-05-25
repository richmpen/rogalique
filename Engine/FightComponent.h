#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"

namespace EngineCore
{

    enum class EnemyType
    {
        Player = 0,
        Enemy,
        None,
    };

    class FightComponent : public Component
    {
    public:
        FightComponent(GameObject* gameObject);

        void Update(float deltaTime) override;
        void Render() override;

        void TakeDamage(int amount);
        void Die();

        void SetDamage(int damage);
        int GetDamage();

        void SetHealth(int health);
        int GetHealth();

        void SetTargetType(EnemyType type);
        EnemyType GetTargetType() const;
    private:
        int damage;
        int health;
        EnemyType targetType;

        float flashTimer = 0.0f;
        float attackCooldown = 0.0f;

        SpriteColliderComponent* collider;
        SpriteRendererComponent* renderer;
    };
}
