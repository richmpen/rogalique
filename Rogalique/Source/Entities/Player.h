#pragma once
#include "../EntitySystem/Systems/RenderSystem.h"
#include "CameraComponent.h"
#include "FightComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "InputComponent.h"
#include "SpriteRendererComponent.h"
#include "Vector.h"
namespace Rogalique {
class Player {
   public:
    Player(const EngineCore::Vector2Df& position, const TargetType& target,
           int damage, int health, int armor);
    EngineCore::GameObject* GetGameObject();

   private:
    EngineCore::GameObject* gameObject;
};

}  // namespace Rogalique
