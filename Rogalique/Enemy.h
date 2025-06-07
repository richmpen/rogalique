#pragma once
#include "CameraComponent.h"
#include "DirectionComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "InputComponent.h"
#include "MoveComponent.h"
#include "RenderSystem.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"

#include <FightComponent.h>

namespace Rogalique {

class Enemy {
   public:
    Enemy(const EngineCore::Vector2Df& position,
          const EngineCore::EnemyType& target, int damage, int health);
    EngineCore::GameObject* GetGameObject();
    float GetSpeed() { return speed; }

   private:
    EngineCore::GameObject* gameObject;
    float speed = 300.f;
};
}  // namespace Rogalique
