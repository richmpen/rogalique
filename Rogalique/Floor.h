#pragma once
#include "Vector.h"
#include "GameWorld.h"
#include "SpriteRendererComponent.h"

namespace Rogalique
{
    class Floor
    {
    public:
        Floor(const EngineCore::Vector2Df& position);
        EngineCore::GameObject* GetGameObject();
    private:
        EngineCore::GameObject* gameObject;
    };
    
}
