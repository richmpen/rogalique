#include "DeveloperLevel.h"

#include "AmmoItem.h"
#include "ArmorItem.h"
#include "EnemyAIComponent.h"
#include "EnemyFactory.h"
#include "ItemType.h"
#include "MazeGenerator.h"
#include "ObjectSpawner.h"
#include "HUDGenerator.h"
#include "UiElement.h"
#include "UiManager.h"
#include "HealthPotion.h"
#include "InventorySystem.h"
#include "WeaponItem.h"
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

    // Create player
    player =
        std::make_unique<Player>(std::forward<EngineCore::Vector2Df>(
                                     {levelWidth / 2 * spritePanelSize, 200}),
                                 TargetType::Player, 15, 100, 100);
   

    // Create music if enabled
    if (SettingsState::musicEnabled) {
        music = std::make_unique<Music>("MetalHell");
    }

    // Spawn enemies if enabled - simple check
    if (SettingsState::enemiesEnabled) {
        ObjectSpawner spawner(this);
        spawner.Spawn(1, EnemyType::CACODEMON, {550, 500}, TargetType::Enemy, 15, 150, 150);
        spawner.Spawn(1, EnemyType::CREEPER, {300, 300}, TargetType::Enemy, 75, 1, 200);
    }

    // Item spawning
    auto healthPotion = std::make_shared<HealthPotion>(ItemType::HEALTH_POTION, 2, sf::Vector2f(10, -100), "HealthItem");
    items.push_back(healthPotion);
    
    auto armorItem = std::make_shared<ArmorItem>(ItemType::ARMOR, 1, sf::Vector2f(300, -100), "ArmorItem");
    items.push_back(armorItem);

    auto ammoItem = std::make_shared<AmmoItem>(ItemType::AMMO, 5, sf::Vector2f(600, -100), "AmmoItem");
    items.push_back(ammoItem);

    auto weapon = std::make_shared<WeaponItem>(ItemType::WEAPON, 1, sf::Vector2f(900, -100), "WeaponItem");
    items.push_back(weapon);
}

void DeveloperLevel::Restart() {
    Stop();
    Start();
}

void DeveloperLevel::Stop() {
    GameWorld::Instance()->Clear();
}

}  // namespace Rogalique