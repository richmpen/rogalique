#pragma once
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "Vector.h"

namespace Rogalique {
class Floor {
   public:
    Floor(const EngineCore::Vector2Df& position);
    Floor(const EngineCore::Vector2Df& position, int textureMapIndex);
    EngineCore::GameObject* GetGameObject();

   private:
    EngineCore::GameObject* gameObject;
};

}  // namespace Rogalique
