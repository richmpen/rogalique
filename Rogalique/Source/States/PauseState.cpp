#include "PauseState.h"

#include "GameSettings.h"
#include "GameStateManager.h"
#include "ImageUI.h"
#include "MainMenuState.h"
#include "PlayState.h"

namespace Rogalique {

PauseState::PauseState() {
    EngineCore::GameWorld::Instance()->SetPaused(true);
    
    auto uiGameObject = EngineCore::GameWorld::Instance()->CreateGameObject("PauseUI");
    uiManager = std::make_shared<UiManager>(uiGameObject);
    CreateUI();
    currentLevel = std::make_unique<DeveloperLevel>();
}

PauseState::~PauseState() {
    EngineCore::GameWorld::Instance()->SetPaused(false);
}


void PauseState::Update(float deltaTime) {
    if (uiManager) {
        uiManager->Update(deltaTime);
    }
}

void PauseState::Render() {
    
    uiManager->Render();
}

void PauseState::CreateUI() {
    if (!uiManager) {
        LOG_ERROR("Cannot create UI - uiManager is null");
        return;
    }

    
    
    auto background = std::make_shared<ImageUI>(
                "panel", sf::Vector2f(0.5, 0.5), sf::Vector2f(static_cast<float>(SETTINGS.SCREEN_WIDTH)/2, static_cast<float>(SETTINGS.SCREEN_HEIGHT)/2));
    background->SetCenterOrigin();
    uiManager->AddElement(background);
    
    continueButton = std::make_shared<ButtonUI>(
        "Continue",
        "UiMap2",
                sf::IntRect(1649,1524,1216,182),
        sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f),
        sf::Vector2f(400.f, 50.f),
                sf::Color::Green
    );
        continueButton->SetCenterOrigin();
            
    if (continueButton) {
        continueButton->SetOnClick([]() {
            LOG_INFO("Play button clicked - starting game");
            GameWorld::Instance()->SetPaused(false);
            EngineCore::GameStateManager::Instance()->PopState();
            
        });
        uiManager->AddElement(continueButton);
    }
        

        
    backToMenuButton = std::make_shared<ButtonUI>(
        "Back to menu",
        "UiMap2",
                sf::IntRect(1649,1524,1216,182),
        sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT / 2.f + 80.f),
        sf::Vector2f(400.f, 50.f),
                sf::Color::Green
    );
    backToMenuButton->SetCenterOrigin();
            
    if (backToMenuButton) {
        backToMenuButton->SetOnClick([this]() {
            LOG_INFO("Exit button clicked - closing game");
            
                currentLevel->Stop();
                
                EngineCore::GameWorld::Instance()->Clear();
                EngineCore::GameStateManager::Instance()->ChangeState(std::make_unique<MainMenuState>());
            
        });
        uiManager->AddElement(backToMenuButton);
    }

    
}
void PauseState::HandleEvent(const sf::Event& event) {
    if (uiManager) {
        for (auto& element : uiManager->GetAllElements()) {
            if (element && element->HandleEvent(event)) {
                return; 
            }
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                EngineCore::GameStateManager::Instance()->PopState();
            }
        }
    }
}
}