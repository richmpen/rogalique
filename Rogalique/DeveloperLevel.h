#pragma once
#include <iostream>
#include <array>
#include "Scene.h"
#include "Player.h"
#include "Music.h"
#include "Enemy.h"
#include "Floor.h"
#include "Wall.h"

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

        float levelWidth = 20;
        float levelHeight = 10;

        std::vector<std::unique_ptr<Wall>> walls;
        std::vector<std::unique_ptr<Floor>> floors;
        
        std::shared_ptr<Player> player;
        std::shared_ptr<Enemy> enemy;
        std::shared_ptr<Music> music;
        std::shared_ptr<Wall> wall;
        std::shared_ptr<Floor> floor;
    };

}
