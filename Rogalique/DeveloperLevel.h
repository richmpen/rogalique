#pragma once
#include "Enemy.h"
#include "Floor.h"
#include "Music.h"
#include "Player.h"
#include "Scene.h"
#include "Wall.h"

#include <array>
#include <iostream>

using namespace EngineCore;

namespace Rogalique {
class DeveloperLevel : public Scene {
   public:
    void Start() override;
    void Restart() override;
    void Stop() override;

    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Floor>> floors;

   private:
    template <typename T>
    void LoadObjectCheck(const std::shared_ptr<T>& object) {
        if (object && object->GetGameObject()) {
            LOG_INFO(object->GetGameObject()->GetName()
                     << " declared at level: " << levelName);
        } else {
            LOG_WARN("Object not valid at level: " << levelName);
        }
    }

    std::string levelName = "Developer Level";

    int levelWidth = 15;
    int levelHeight = 15;

    std::shared_ptr<Player> player;
    std::shared_ptr<Enemy> enemy;
    std::shared_ptr<Music> music;
    std::shared_ptr<Wall> wall;
    std::shared_ptr<Floor> floor;
};

}  // namespace Rogalique
