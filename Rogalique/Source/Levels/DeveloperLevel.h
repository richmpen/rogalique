#pragma once

#include "Enemy.h"
#include "EnemyFactory.h"
#include "Floor.h"
#include "Music.h"
#include "Player.h"
#include "Scene.h"
#include "Ui/UiManager.h"
#include "Wall.h"
#include "Item.h"
#include <memory>

#include <array>
#include <iostream>

using namespace EngineCore;

namespace Rogalique {
class DeveloperLevel : public Scene {
   public:
    DeveloperLevel();

    void Start() override;
    void Restart() override;
    void Stop() override;

    std::vector<std::unique_ptr<Wall>> walls;
    std::vector<std::unique_ptr<Floor>> floors;
    std::unordered_map<EnemyType, std::unique_ptr<EnemyFactory>> enemyFactories;
    std::vector<std::shared_ptr<Enemy>> enemys;
    std::vector<std::shared_ptr<Item>> items;

   private:

    std::string levelName = "Developer Level";
    float levelWidth = 15;
    float levelHeight = 15;
    float spritePanelSize = 100;
    int indentMaze = -2;

    std::shared_ptr<Player> player;
    std::shared_ptr<Wall> wall;
    std::shared_ptr<Floor> floor;
    std::shared_ptr<Music> music;
    std::shared_ptr<UiManager> uiManager;
};

}  // namespace Rogalique
