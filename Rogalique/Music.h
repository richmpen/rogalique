#pragma once

#include <GameObject.h>
#include <GameWorld.h>
#include <SoundComponent.h>
#include <ResourceSystem.h>

namespace Rogalique
{
    class Music
    {
    public:
        Music(const std::string& soundName);
    private:
        EngineCore::GameObject* gameObject;
    };
}


