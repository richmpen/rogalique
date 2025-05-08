#pragma once
#include "Vector.h"
#include "GameWorld.h"

namespace Rogalique
{
    class Wall
    {
    public:
        Wall(const EngineCore::Vector2Df& position);
        EngineCore::GameObject* GetGameObject();
    private:
        EngineCore::GameObject* gameObject;
    };
    
}
