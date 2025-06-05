#include "DeveloperLevel.h"

#include "EnemyAIComponent.h"
#include "MazeGenerator.h"

using namespace EngineCore;

namespace Rogalique {
void DeveloperLevel::Start() {
    LOG_INFO("!Started " << levelName);
    float spritePanelWidth = 100;
    float spritePanelHeight = 100;
    int indentMaze = -2;

    for (int y = indentMaze; y < levelWidth + 2; y++) {
        for (int x = indentMaze; x < levelHeight + 2; x++) {
            if (y == indentMaze || y == levelWidth + 1 || x == indentMaze ||
                x == levelHeight + 1) {
                wall = std::make_unique<Wall>(EngineCore::Vector2Df{
                    spritePanelWidth * x, spritePanelHeight * y});
                // LoadObjectCheck(wall);
            } else {
                floor = std::make_unique<Floor>(EngineCore::Vector2Df{
                    spritePanelWidth * x, spritePanelHeight * y});
                // LoadObjectCheck(floor);
            }
        }
    }

    MazeGenerator mazeGenerator(levelWidth, levelHeight, this);
    mazeGenerator.Generate();

    player = std::make_unique<Player>(
        std::forward<EngineCore::Vector2Df>({200, 200}),
        EngineCore::EnemyType::Player, 15, 100);
    LoadObjectCheck(player);
    enemy = std::make_unique<Enemy>(
        std::forward<EngineCore::Vector2Df>({800, 1400}),
        EngineCore::EnemyType::Enemy, 10, 50);
    LoadObjectCheck(enemy);
    music = std::make_unique<Music>("soundtrack");
    LoadObjectCheck(music);
}
void DeveloperLevel::Restart() {
    Stop();
    Start();
    LOG_INFO("!Restarted " << levelName);
}
void DeveloperLevel::Stop() {
    LOG_INFO("!Stopped " << levelName);
    GameWorld::Instance()->Clear();
}

}  // namespace Rogalique