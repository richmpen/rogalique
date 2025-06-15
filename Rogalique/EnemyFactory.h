#pragma once
#include "Enemy.h"
#include "Logger.h"

namespace Rogalique {

class EnemyFactory {
   public:
    virtual std::shared_ptr<Enemy> CreateEnemy(
        const EngineCore::Vector2Df& position,
        const EngineCore::TargetType& target, int damage, int health,
        float speed) = 0;
};

class CacodemonEnemyFactory final : public EnemyFactory {
   public:
    std::shared_ptr<Enemy> CreateEnemy(const EngineCore::Vector2Df& position,
                                       const EngineCore::TargetType& target,
                                       int damage, int health,
                                       float speed) override;
    ~CacodemonEnemyFactory() = default;
};

class CreeperEnemyFactory final : public EnemyFactory {
   public:
    std::shared_ptr<Enemy> CreateEnemy(const EngineCore::Vector2Df& position,
                                       const EngineCore::TargetType& target,
                                       int damage, int health,
                                       float speed) override;
    ~CreeperEnemyFactory() = default;
};
}  // namespace Rogalique
