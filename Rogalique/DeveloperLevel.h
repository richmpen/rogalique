#pragma once
#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "Music.h"

using namespace EngineCore;

namespace Rogalique
{
    class DeveloperLevel : public Scene
    {
    public:
        void Start() override;
        void Restart() override;
        void Stop() override;
    private:
        std::shared_ptr<Player> player;
        std::shared_ptr<Music> music;
    };

}
