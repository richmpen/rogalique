#include "SettingsState.h"
#include "GameSettings.h"
#include "GameStateManager.h"
#include "GameWorld.h"
#include "SoundComponent.h"
#include "EnemyAIComponent.h"

namespace Rogalique {

bool SettingsState::musicEnabled = true;
bool SettingsState::mazeEnabled = true;
bool SettingsState::enemiesEnabled = true;

SettingsState::SettingsState() {
    auto uiGameObject = EngineCore::GameWorld::Instance()->CreateGameObject("SettingsUI");
    uiManager = std::make_shared<UiManager>(uiGameObject);
    CreateUI();
}

SettingsState::~SettingsState() {
}

void SettingsState::Update(float deltaTime) {
    if (uiManager) {
        uiManager->Update(deltaTime);
    }
}

void SettingsState::Render() {
    if (uiManager) {
        uiManager->Render();
    }
}

void SettingsState::HandleEvent(const sf::Event& event) {
    if (uiManager) {
        for (auto& element : uiManager->GetAllElements()) {
            if (element && element->HandleEvent(event)) {
                return;
            }
        }
    }
    
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            EngineCore::GameStateManager::Instance()->PopState();
        }
    }
}

void SettingsState::CreateUI() {
    if (!uiManager) {
        return;
    }
    
    background = std::make_shared<ImageUI>(
        "menu_bg", sf::Vector2f(1, 1), 
        sf::Vector2f(static_cast<float>(SETTINGS.SCREEN_WIDTH)/2, static_cast<float>(SETTINGS.SCREEN_HEIGHT)/2));
    background->SetCenterOrigin();
    uiManager->AddElement(background);
    
    titleText = std::make_shared<TextUI>(48, sf::Vector2f(static_cast<float>(SETTINGS.SCREEN_WIDTH)/2, 100.f), true);
    titleText->SetText("SETTINGS", true);
    titleText->SetColor(sf::Color::White);
    uiManager->AddElement(titleText);
    
    backButton = std::make_shared<ButtonUI>(
        "Back",
        "UiMap2",
        sf::IntRect(1649, 1524, 1216, 182),
        sf::Vector2f(100.f, 100.f),
        sf::Vector2f(150.f, 40.f),
        sf::Color::Red
    );
    backButton->SetCenterOrigin();
    backButton->SetOnClick([]() {
        EngineCore::GameStateManager::Instance()->PopState();
    });
    uiManager->AddElement(backButton);
    
    tabsSystem = std::make_shared<TabsUI>(
        sf::Vector2f(200.f, 200.f),
        sf::Vector2f(800.f, 600.f)
    );
    
    tabsSystem->AddTab("Audio");
    tabsSystem->AddTab("Gameplay");
    
    uiManager->AddElement(tabsSystem);
    
    CreateAudioTab();
    CreateGameplayTab();
}

void SettingsState::CreateAudioTab() {
    
    auto musicCheckbox = std::make_shared<CheckBoxUI>(
        "Enable Music", sf::Vector2f(170.f, 280.f), musicEnabled);
    musicCheckbox->SetOnValueChanged([this](bool value) {
        musicEnabled = value;
        ToggleMusic(value);
    });
    tabsSystem->AddElementToTab(SETTINGS.AUDIO_TAB, musicCheckbox);
}

void SettingsState::CreateGameplayTab() {
    float spacing = 50.f;
    
    
    auto mazeCheckbox = std::make_shared<CheckBoxUI>(
        "Enable Maze Generation", sf::Vector2f(170.f, 280.f), mazeEnabled);
    mazeCheckbox->SetOnValueChanged([this](bool value) {
        mazeEnabled = value;
    });
    tabsSystem->AddElementToTab(SETTINGS.GAMEPLAY_TAB, mazeCheckbox);
    
    auto enemiesCheckbox = std::make_shared<CheckBoxUI>(
        "Enable Enemies", sf::Vector2f(170.f, 280.f + spacing), enemiesEnabled);
    enemiesCheckbox->SetOnValueChanged([this](bool value) {
        enemiesEnabled = value;
        ToggleEnemies(value);
    });
    tabsSystem->AddElementToTab(SETTINGS.GAMEPLAY_TAB, enemiesCheckbox);
}

void SettingsState::ToggleMusic(bool enable) {
    auto gameObjects = EngineCore::GameWorld::Instance()->GetAllGameObjects();
    
    for (auto& gameObject : gameObjects) {
        auto soundComponent = gameObject->GetComponent<EngineCore::SoundComponent>();
        if (soundComponent) {
            if (enable) {
                soundComponent->Start();
            } else {
                soundComponent->Stop();
            }
        }
    }
}

void SettingsState::ToggleEnemies(bool enable) {
    if (!enable) {
        auto gameObjects = EngineCore::GameWorld::Instance()->GetAllGameObjects();
        
        for (auto& gameObject : gameObjects) {
     
            if (gameObject->GetComponent<EnemyAIComponent>()) {
                EngineCore::GameWorld::Instance()->DestroyGameObject(gameObject);
            }
        }
    }
}

}

