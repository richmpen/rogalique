#pragma once
#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "DirectionComponent.h"
#include "MoveComponent.h"
#include "SpriteColliderComponent.h"
#include "GameObject.h"

namespace Rogalique {

	class Enemy
    {
    public:
        Enemy(const EngineCore::Vector2Df& position);
        EngineCore::GameObject* GetGameObject();
    private:
        EngineCore::GameObject* gameObject;
    };
}

