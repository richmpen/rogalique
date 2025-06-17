#include "ObjectSpawner.h"

namespace Rogalique {
ObjectSpawner::ObjectSpawner(DeveloperLevel* level) : level(level) {}

void ObjectSpawner::Spawn(int count, EnemyType type,
                          const EngineCore::Vector2Df& position,
                          TargetType target, int damage, int health,
                          float speed) {
    auto it = level->enemyFactories.find(type);
    if (it == level->enemyFactories.end()) {
        LOG_WARN("No factory found for enemy type");
        return;
    }

    EnemyFactory* factory = it->second.get();

    for (int i = 0; i < count; ++i) {
        EngineCore::Vector2Df spawnPos = position;
        spawnPos.x += rand() % 100 - 25;
        spawnPos.y += rand() % 100 - 25;

        std::shared_ptr<Enemy> enemy =
            factory->CreateEnemy(spawnPos, target, damage, health, speed);
        if (enemy && enemy->GetGameObject()) {
            LOG_INFO("Spawned " << enemy->GetGameObject()->GetName()
                                << " at position (" << spawnPos.x << ", "
                                << spawnPos.y << ")");
            level->enemys.push_back(std::move(enemy));
        } else {
            LOG_ERROR("Failed to spawn enemy: gameObject is nullptr");
        }
    }
}
}  // namespace Rogalique
