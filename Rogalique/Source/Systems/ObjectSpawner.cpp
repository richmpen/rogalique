#include "ObjectSpawner.h"
#include "Logger.h"



namespace Rogalique {
ObjectSpawner::ObjectSpawner(DeveloperLevel* level) : level(level) {}

void ObjectSpawner::SpawnEnemy(int count, EnemyType type,
                          const EngineCore::Vector2Df& position,
                          TargetType target, int damage, int health,
                          float speed) const {
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
            level->enemys.push_back(std::move(enemy));
        } else {
            LOG_ERROR("Failed to spawn enemy: gameObject is nullptr");
        }
    }
}

void ObjectSpawner::SpawnItem(ItemType type, int count, const EngineCore::Vector2Df& position,const std::string& textureName) {
    auto it = level->itemFactories.find(type);
    if (it == level->itemFactories.end()) {
        LOG_WARN("No factory found for item type");
        return;
    }

    ItemFactory* factory = it->second.get();
    
    std::shared_ptr<Item> item =
        factory->CreateItem(type, count, position, textureName);
    if (item && item->GetGameObject()) {
        level->items.push_back(std::move(item));
    } else {
        LOG_ERROR("Failed to spawn item: gameObject is nullptr");
    }
}

}  // namespace Rogalique
