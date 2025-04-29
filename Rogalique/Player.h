#pragma once
#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "SpriteColliderComponent.h"
#include "GameObject.h"

namespace Rogalique
{
    class Player
    {
    public:
        Player();
        EngineCore::GameObject* GetGameObject();
    private:
        EngineCore::GameObject* gameObject;
    };
    
}
