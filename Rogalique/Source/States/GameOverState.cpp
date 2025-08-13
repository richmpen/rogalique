#include "GameOverState.h"

#include "GameSettings.h"
#include "GameStateManager.h"
#include "GameWorld.h"
#include "MainMenuState.h"
#include "PlayState.h"

namespace Rogalique {

GameOverState::GameOverState() {
    EngineCore::GameWorld::Instance()->SetPaused(true);

    auto uiGameObject =
        EngineCore::GameWorld::Instance()->CreateGameObject("GameOverUI");
    uiManager = std::make_shared<UiManager>(uiGameObject);
    CreateUI();
}

GameOverState::~GameOverState() {
    EngineCore::GameWorld::Instance()->SetPaused(false);
}

void GameOverState::Update(float deltaTime) {
    if (uiManager) {
        uiManager->Update(deltaTime);
    }
}

void GameOverState::Render() {
    if (uiManager) {
        uiManager->Render();
    }
}

void GameOverState::HandleEvent(const sf::Event& event) {
    if (uiManager) {
        for (auto& element : uiManager->GetAllElements()) {
            if (element && element->HandleEvent(event)) {
                return;
            }
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            EngineCore::GameStateManager::Instance()->ChangeState(
                std::make_shared<MainMenuState>());
        }
    }
}

void GameOverState::CreateUI() {
    if (!uiManager) {
        return;
    }

    background = std::make_shared<ImageUI>(
        "panel", sf::Vector2f(0.6f, 0.6f),
        sf::Vector2f(static_cast<float>(SETTINGS.SCREEN_WIDTH) / 2,
                     static_cast<float>(SETTINGS.SCREEN_HEIGHT) / 2));
    background->SetCenterOrigin();
    uiManager->AddElement(background);

    titleText = std::make_shared<TextUI>(
        60, sf::Vector2f(static_cast<float>(SETTINGS.SCREEN_WIDTH) / 2, 350.f),
        true);
    titleText->SetText("GAME OVER", true);
    titleText->SetColor(sf::Color::Red);
    uiManager->AddElement(titleText);

    restartButton = std::make_shared<ButtonUI>(
        "Restart", "UiMap2", sf::IntRect(1649, 1524, 1216, 182),
        sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f),
        sf::Vector2f(400.f, 50.f), sf::Color::Green);
    restartButton->SetCenterOrigin();
    restartButton->SetOnClick([]() {
        EngineCore::GameWorld::Instance()->Clear();
        EngineCore::GameStateManager::Instance()->ChangeState(
            std::make_shared<PlayState>());
    });
    uiManager->AddElement(restartButton);

    backToMenuButton = std::make_shared<ButtonUI>(
        "Back to Menu", "UiMap2", sf::IntRect(1649, 1524, 1216, 182),
        sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f,
                     SETTINGS.SCREEN_HEIGHT / 2.f + 80.f),
        sf::Vector2f(400.f, 50.f), sf::Color::Green);
    backToMenuButton->SetCenterOrigin();
    backToMenuButton->SetOnClick([]() {
        EngineCore::GameWorld::Instance()->Clear();
        EngineCore::GameStateManager::Instance()->ChangeState(
            std::make_shared<MainMenuState>());
    });
    uiManager->AddElement(backToMenuButton);
}

}  // namespace Rogalique