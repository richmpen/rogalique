#pragma once
#include "DeveloperLevel.h"
#include "Enemy.h"
#include "Item.h"
#include "ItemType.h"
#include <GameObject.h>
#include <stack>
#include <vector>

namespace Rogalique {

class ObjectSpawner {
   public:
    ObjectSpawner(DeveloperLevel* level);

    void SpawnEnemy(int count, EnemyType type, const EngineCore::Vector2Df& position,
               TargetType target, int damage, int health, float speed) const;
    void SpawnItem(ItemType type, int count, const EngineCore::Vector2Df& position,const std::string& textureName);
   private:
    DeveloperLevel* level;
};
}  // namespace Rogalique