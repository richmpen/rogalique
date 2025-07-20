#include "WictoryState.h"

#include "GameSettings.h"
#include "GameStateManager.h"
#include "GameWorld.h"
#include "MainMenuState.h"
#include "PlayState.h"

namespace Rogalique {

VictoryState::VictoryState() {
    EngineCore::GameWorld::Instance()->SetPaused(true);
    
    auto uiGameObject = EngineCore::GameWorld::Instance()->CreateGameObject("VictoryUI");
    uiManager = std::make_shared<UiManager>(uiGameObject);
    CreateUI();
}

VictoryState::~VictoryState() {
    EngineCore::GameWorld::Instance()->SetPaused(false);
}

void VictoryState::Update(float deltaTime) {
    if (uiManager) {
        uiManager->Update(deltaTime);
    }
}

void VictoryState::Render() {
    if (uiManager) {
        uiManager->Render();
    }
}

void VictoryState::HandleEvent(const sf::Event& event) {
    if (uiManager) {
        for (auto& element : uiManager->GetAllElements()) {
            if (element && element->HandleEvent(event)) {
                return;
            }
        }
    }
    
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            EngineCore::GameStateManager::Instance()->ChangeState(std::make_shared<MainMenuState>());
        }
    }
}

void VictoryState::CreateUI() {
    if (!uiManager) {
        return;
    }
    
    background = std::make_shared<ImageUI>(
        "panel", sf::Vector2f(0.7f, 0.7f), 
        sf::Vector2f(static_cast<float>(SETTINGS.SCREEN_WIDTH)/2, static_cast<float>(SETTINGS.SCREEN_HEIGHT)/2));
    background->SetElementOriginCenter();
    uiManager->AddElement(background);
    
    titleText = std::make_shared<TextUI>(60, sf::Vector2f(static_cast<float>(SETTINGS.SCREEN_WIDTH)/2, 320.f), true);
    titleText->SetText("VICTORY!", true);
    titleText->SetColor(sf::Color::Green);
    uiManager->AddElement(titleText);
    
    restartButton = std::make_shared<ButtonUI>(
        "Restart",
        "UiMap2",
        sf::IntRect(1649, 1524, 1216, 182),
        sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f - 40.f),
        sf::Vector2f(400.f, 50.f),
        sf::Color::Green
    );
    restartButton->SetElementOriginCenter();
    restartButton->SetOnClick([]() {
        EngineCore::GameWorld::Instance()->Clear();
        EngineCore::GameStateManager::Instance()->ChangeState(std::make_shared<PlayState>());
    });
    uiManager->AddElement(restartButton);
    
    nextLevelButton = std::make_shared<ButtonUI>(
        "Next Level",
        "UiMap2",
        sf::IntRect(1649, 1524, 1216, 182),
        sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f + 40.f),
        sf::Vector2f(400.f, 50.f),
        sf::Color(128, 128, 128)
    );
    nextLevelButton->SetElementOriginCenter();
    nextLevelButton->SetEnabled(false);
    uiManager->AddElement(nextLevelButton);
    
    backToMenuButton = std::make_shared<ButtonUI>(
        "Back to Menu",
        "UiMap2",
        sf::IntRect(1649, 1524, 1216, 182),
        sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f + 120.f),
        sf::Vector2f(400.f, 50.f),
        sf::Color::Green
    );
    backToMenuButton->SetElementOriginCenter();
    backToMenuButton->SetOnClick([]() {
        EngineCore::GameWorld::Instance()->Clear();
        EngineCore::GameStateManager::Instance()->ChangeState(std::make_shared<MainMenuState>());
    });
    uiManager->AddElement(backToMenuButton);
}

}