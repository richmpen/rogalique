#pragma once
#include "CameraComponent.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"
#include "RenderSystem.h"
#include "InputComponent.h"
#include "GameObject.h"
#include "Vector.h"
#include <FightComponent.h>
namespace Rogalique
{
    class Player
    {
    public:
        Player(const EngineCore::Vector2Df& position, const EngineCore::EnemyType& target, int damage, int health);
        EngineCore::GameObject* GetGameObject();
    private:
        EngineCore::GameObject* gameObject;
    };
    
}
