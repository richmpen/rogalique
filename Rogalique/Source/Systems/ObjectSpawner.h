#pragma once
#include "DeveloperLevel.h"
#include "Enemy.h"

#include <GameObject.h>
#include <stack>
#include <vector>

namespace Rogalique {

class ObjectSpawner {
   public:
    ObjectSpawner(DeveloperLevel* level);

    void Spawn(int count, EnemyType type, const EngineCore::Vector2Df& position,
               TargetType target, int damage, int health, float speed);

   private:
    DeveloperLevel* level;
};
}  // namespace Rogalique