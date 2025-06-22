#include "EnemyFactory.h"

namespace Rogalique {

std::shared_ptr<Enemy> CacodemonEnemyFactory::CreateEnemy(
    const EngineCore::Vector2Df& position, const TargetType& target,
    int damage, int health, float speed) {
    return std::make_shared<Cacodemon>(position, target, damage, health, speed);
}

std::shared_ptr<Enemy> CreeperEnemyFactory::CreateEnemy(
    const EngineCore::Vector2Df& position, const TargetType& target,
    int damage, int health, float speed) {
    return std::make_shared<Creeper>(position, target, damage, health, speed);
}
}  // namespace Rogalique