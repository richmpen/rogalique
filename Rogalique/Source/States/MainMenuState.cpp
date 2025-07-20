#include "MainMenuState.h"

#include "GameSettings.h"
#include "GameStateManager.h"
#include "PlayState.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"
#include "GameWorld.h"
#include "SettingsState.h"
#include "TextUI.h"

namespace Rogalique {
    MainMenuState::MainMenuState() {
        auto uiGameObject = EngineCore::GameWorld::Instance()->CreateGameObject("MainMenuUI");
        uiManager = std::make_shared<UiManager>(uiGameObject);
        CreateUI();
    }

    void MainMenuState::CreateUI() {
        if (!uiManager) {
            LOG_ERROR("Cannot create UI - uiManager is null");
            return;
        }
        
        background = std::make_shared<ImageUI>(
                "menu_bg", sf::Vector2f(1, 1), sf::Vector2f(static_cast<float>(SETTINGS.SCREEN_WIDTH)/2, static_cast<float>(SETTINGS.SCREEN_HEIGHT)/2));
        background->SetElementOriginCenter();
        uiManager->AddElement(background);
    
        logo = std::make_shared<ImageUI>(
                "logo", sf::Vector2f(0.4f,0.4f), sf::Vector2f(300, 150));
        logo->SetElementOriginCenter();
        uiManager->AddElement(logo);
    
        playButton = std::make_shared<ButtonUI>(
            "Play",
            "UiMap2",
            sf::IntRect(1649,1524,1216,182),
            sf::Vector2f(300.f, 400.f),
            sf::Vector2f(400.f, 50.f),
            sf::Color::Red
        );
        
        if (playButton) {
            playButton->SetOnClick([]() {
                EngineCore::GameStateManager::Instance()->ChangeState(
                    std::make_shared<PlayState>()
                );
            });
            uiManager->AddElement(playButton);
        }
        playButton->SetElementColor(sf::Color::Green);
        playButton->SetElementOriginCenter();
        

        settingsButton = std::make_shared<ButtonUI>(
                "Settings",
                "UiMap2",
            sf::IntRect(1649,1524,1216,182),
                sf::Vector2f(320.f, 400.f + 80.f),
                sf::Vector2f(400.f, 50.f),
            sf::Color::Green
            );
        settingsButton->SetElementOriginCenter();
        if (settingsButton) {
            settingsButton->SetOnClick([]() {
                EngineCore::GameStateManager::Instance()->PushState(
                    std::make_shared<SettingsState>());
            });
            uiManager->AddElement(settingsButton);
        }

        
        exitButton = std::make_shared<ButtonUI>(
            "Exit",
            "UiMap2",
            sf::IntRect(1649,1524,1216,182),
            sf::Vector2f(340.f, 400.f + 160.f),
            sf::Vector2f(400.f, 50.f),
            sf::Color::Green
        );
        exitButton->SetElementOriginCenter();
        
        if (exitButton) {
            exitButton->SetOnClick([]() {
                EngineCore::RenderSystem::Instance()->GetMainWindow().close();
            });
            uiManager->AddElement(exitButton);
        }
    }

    void MainMenuState::Update(float deltaTime) {
        if (uiManager) {
            uiManager->Update(deltaTime);
        }
    }

    void MainMenuState::Render() {
        uiManager->Render();
    }

    void MainMenuState::HandleEvent(const sf::Event& event) {
        if (uiManager) {
            for (auto& element : uiManager->GetAllElements()) {
                if (element && element->HandleEvent(event)) {
                    return;
                }
            }
        }
    }
}  // namespace Rogalique