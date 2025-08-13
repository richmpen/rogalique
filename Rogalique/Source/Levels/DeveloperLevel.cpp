#include "DeveloperLevel.h"
#include "Item.h"

#include "EnemyAIComponent.h"
#include "EnemyFactory.h"
#include "ItemFactory.h"
#include "ItemType.h"
#include "MazeGenerator.h"
#include "ObjectSpawner.h"
#include "HUDGenerator.h"
#include "UiElement.h"
#include "UiManager.h"

#include "InventorySystem.h"

#include "States/SettingsState.h"

using namespace EngineCore;

namespace Rogalique {

DeveloperLevel::DeveloperLevel() {}

void DeveloperLevel::Start() {
    // Arrangement of wall and floor objects
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
    
    // Create maze if enabled - simple check
    if (SettingsState::mazeEnabled) {
        MazeGenerator mazeGenerator(static_cast<float>(levelWidth),
                                    static_cast<float>(levelHeight), this);
        mazeGenerator.Generate();
    }

    // Initialize enemy factories if enabled - simple check
    if (SettingsState::enemiesEnabled) {
        enemyFactories.emplace(EnemyType::CACODEMON,
                               std::make_unique<CacodemonEnemyFactory>());
        enemyFactories.emplace(EnemyType::CREEPER,
                               std::make_unique<CreeperEnemyFactory>());
    }
    itemFactories.emplace(ItemType::HEALTH_POTION,
                            std::make_unique<HealthItemFactory>());
    itemFactories.emplace(ItemType::ARMOR,
                            std::make_unique<ArmorItemFactory>());
    itemFactories.emplace(ItemType::AMMO,
                            std::make_unique<AmmoItemFactory>());
    itemFactories.emplace(ItemType::WEAPON,
                            std::make_unique<WeaponItemFactory>());

    // Create player
    player =
        std::make_unique<Player>(std::forward<EngineCore::Vector2Df>(
                                     {levelWidth / 2 * spritePanelSize, 200}),
                                 TargetType::Player, 15, 100, 100);
   

    // Create music if enabled
    if (SettingsState::musicEnabled) {
        music = std::make_unique<Music>("MetalHell");
    }

    ObjectSpawner spawner(this);
    // Spawn enemies if enabled - simple check
    if (SettingsState::enemiesEnabled) {
        spawner.SpawnEnemy(1, EnemyType::CACODEMON, {550, 500}, TargetType::Enemy, 15, 150, 150);
        spawner.SpawnEnemy(0, EnemyType::CREEPER, {300, 300}, TargetType::Enemy, 75, 1, 200);
    }

    // Item spawning
    spawner.SpawnItem(ItemType::HEALTH_POTION, 2, EngineCore::Vector2Df(10, -100), "HealthItem");
    spawner.SpawnItem(ItemType::ARMOR, 1, EngineCore::Vector2Df(300, -100), "ArmorItem");
    spawner.SpawnItem(ItemType::AMMO, 5, EngineCore::Vector2Df(600, -100), "AmmoItem");
    spawner.SpawnItem(ItemType::WEAPON, 1, EngineCore::Vector2Df(900, -100), "WeaponItem");
    
}

void DeveloperLevel::Restart() {
    Stop();
    Start();
}

void DeveloperLevel::Stop() {
    GameWorld::Instance()->Clear();
}

}  // namespace Rogalique