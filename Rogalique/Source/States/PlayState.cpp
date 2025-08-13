#include "PlayState.h"

#include "EnemyAIComponent.h"
#include "GameOverState.h"
#include "GameStateManager.h"
#include "GameWorld.h"
#include "HUDGenerator.h"
#include "HealthComponent.h"
#include "InventoryState.h"
#include "InventorySystem.h"
#include "Logger.h"
#include "MainMenuState.h"
#include "PauseState.h"
#include "RenderSystem.h"
#include "SettingsState.h"
#include "VictoryState.h"

namespace Rogalique {
PlayState::PlayState() {
    EngineCore::GameWorld::Instance()->Clear();
    currentLevel = std::make_unique<DeveloperLevel>();
    currentLevel->Start();
    EngineCore::GameWorld::SetPaused(false);

    auto uiGameObject =
        EngineCore::GameWorld::Instance()->CreateGameObject("PlayStateUI");
    uiManager = uiGameObject->AddComponent<UiManager>();

    gameObject = EngineCore::GameWorld::Instance()->FindPlayer();

    HUDGenerator hudGenerator(uiManager, gameObject);
    hudGenerator.Generate();
}

void PlayState::Update(float deltaTime) {
    if (uiManager) {
        uiManager->Update(deltaTime);
    }

    CheckGameStates();
}

void PlayState::Render() {
    if (uiManager) {
        uiManager->Render();
    }
}

void PlayState::HandleEvent(const sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            GameWorld::Instance()->SetPaused(true);
            EngineCore::GameStateManager::Instance()->PushState(
                std::make_shared<PauseState>());
            return;
        }
        if (event.key.code == sf::Keyboard::Tab) {
            GameWorld::Instance()->SetPaused(true);
            EngineCore::GameStateManager::Instance()->PushState(
                std::make_unique<InventoryState>());
        }

        if (event.key.code == sf::Keyboard::Num1) {
            InventorySystem::Instance()->UseEquippedItem(0);
        }
        if (event.key.code == sf::Keyboard::Num2) {
            InventorySystem::Instance()->UseEquippedItem(1);
        }
        if (event.key.code == sf::Keyboard::Num3) {
            InventorySystem::Instance()->UseEquippedItem(2);
        }
    }
}

void PlayState::CheckGameStates() {
    // Check player death
    auto player = EngineCore::GameWorld::Instance()->FindPlayer();
    if (!player) {
        EngineCore::GameStateManager::Instance()->ChangeState(
            std::make_shared<GameOverState>());
        return;
    }

    // Check victory condition only if enemies are enabled in settings
    if (SettingsState::enemiesEnabled) {
        bool hasEnemies = false;
        auto gameObjects =
            EngineCore::GameWorld::Instance()->GetAllGameObjects();
        for (auto& gameObject : gameObjects) {
            if (gameObject->GetComponent<EnemyAIComponent>()) {
                hasEnemies = true;
                break;
            }
        }

        if (!hasEnemies) {
            EngineCore::GameStateManager::Instance()->ChangeState(
                std::make_shared<VictoryState>());
        }
    }
    // If enemies are disabled, no victory condition is checked
}

void PlayState::PauseGame() {
    if (!isPaused) {
        isPaused = true;
        EngineCore::GameWorld::SetPaused(true);
    }
}

void PlayState::UnpauseGame() {
    if (isPaused) {
        isPaused = false;
        EngineCore::GameWorld::SetPaused(false);
    }
}

void PlayState::TogglePause() {
    if (isPaused) {
        UnpauseGame();
    } else {
        PauseGame();
    }
}

}  // namespace Rogalique
