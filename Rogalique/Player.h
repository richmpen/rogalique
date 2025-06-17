#pragma once
#include "CameraComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "InputComponent.h"
#include "RenderSystem.h"
#include "SpriteRendererComponent.h"
#include "Vector.h"

#include <FightComponent.h>
namespace Rogalique {
class Player {
   public:
    Player(const EngineCore::Vector2Df& position,
           const EngineCore::TargetType& target, int damage, int health);
    EngineCore::GameObject* GetGameObject();

   private:
    EngineCore::GameObject* gameObject;
};

}  // namespace Rogalique
