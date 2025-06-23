#pragma once

#include "FightComponent.h"

namespace Rogalique {

enum class EnemyType {
    CACODEMON,
    CREEPER,
};

class Enemy {
   public:
    Enemy() = default;
    virtual ~Enemy() = default;

    EngineCore::GameObject* GetGameObject();

   protected:
    EngineCore::GameObject* gameObject;
};

class Cacodemon : public Enemy {
   public:
    Cacodemon(const EngineCore::Vector2Df& position, const TargetType& target,
              int damage, int health, float speed);
    ~Cacodemon() {}
};

class Creeper : public Enemy {
   public:
    Creeper(const EngineCore::Vector2Df& position, const TargetType& target,
            int damage, int health, float speed);
    ~Creeper() {}
};
}  // namespace Rogalique
