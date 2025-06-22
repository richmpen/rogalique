#pragma once
#include "GameWorld.h"
#include "Vector.h"

namespace Rogalique {
class Wall {
   public:
    Wall(const EngineCore::Vector2Df& position);
    Wall(const EngineCore::Vector2Df position, int textureMapIndex);
    EngineCore::GameObject* GetGameObject();

   private:
    EngineCore::GameObject* gameObject;
};

}  // namespace Rogalique
