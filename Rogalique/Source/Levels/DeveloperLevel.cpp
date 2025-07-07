#include "DeveloperLevel.h"

#include "EnemyAIComponent.h"
#include "EnemyFactory.h"
#include "MazeGenerator.h"
#include "ObjectSpawner.h"
#include "Ui/HUDGenerator.h"
#include "UiElement.h"
#include "UiManager.h"

using namespace EngineCore;

namespace Rogalique {

DeveloperLevel::DeveloperLevel() {}

void DeveloperLevel::Start() {
    LOG_INFO("!Started " << levelName);

    // Arrangement of wall and floor objects regardless of the connection of the
    // labyrinth or other objects
    for (int y = indentMaze; y < levelWidth + 2; y++) {
        for (int x = indentMaze; x < levelHeight + 2; x++) {
            if (y == indentMaze || y == levelWidth + 1 || x == indentMaze ||
                x == levelHeight + 1) {
                wall = std::make_unique<Wall>(EngineCore::Vector2Df{
                    spritePanelSize * x, spritePanelSize * y});
            } else {
                floor = std::make_unique<Floor>(EngineCore::Vector2Df{
                    spritePanelSize * x, spritePanelSize * y});
            }
        }
    }
    // Labyrinth spawn object
    MazeGenerator mazeGenerator(static_cast<float>(levelWidth),
                                static_cast<float>(levelHeight), this);
    mazeGenerator.Generate();

    // Initializing enemy factories
    enemyFactories.emplace(EnemyType::CACODEMON,
                           std::make_unique<CacodemonEnemyFactory>());
    enemyFactories.emplace(EnemyType::CREEPER,
                           std::make_unique<CreeperEnemyFactory>());

    // Initialization of objects
    player =
        std::make_unique<Player>(std::forward<EngineCore::Vector2Df>(
                                     {levelWidth / 2 * spritePanelSize, 200}),
                                 TargetType::Player, 15, 100, 100);
    LoadObjectCheck(player);

    music = std::make_unique<Music>("MetalHell");

    // Enemy Spawners (Requires factory initialization)
    ObjectSpawner spawner(this);
    spawner.Spawn(1, EnemyType::CACODEMON, {550, 500}, TargetType::Enemy, 1, 30,
                  150);
    spawner.Spawn(0, EnemyType::CREEPER, {300, 300}, TargetType::Enemy, 1, 20,
                  200);

    // UI
    auto uiGameObject = GameWorld::Instance()->CreateGameObject("UI_Manager");
    auto uiManagerRaw = uiGameObject->AddComponent<Rogalique::UiManager>();
    uiManager = std::shared_ptr<UiManager>(uiManagerRaw);

    HUDGenerator hudGenerator(uiManager, this, player->GetGameObject());
    hudGenerator.Generate();
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

template <typename T>
void DeveloperLevel::LoadObjectCheck(const std::shared_ptr<T>& object) {
    if (object && object->GetGameObject()) {
        LOG_INFO(object->GetGameObject()->GetName()
                 << " declared at level: " << levelName);
    } else {
        LOG_WARN(object->GetGameObject()->GetName()
                 << " not valid at level: " << levelName);
    }
}
}  // namespace Rogalique