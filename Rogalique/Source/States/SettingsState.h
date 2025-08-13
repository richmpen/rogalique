#pragma once
#include "GameState.h"
#include "UiManager.h"
#include "TabsUI.h"
#include "CheckBoxUI.h"
#include "ButtonUI.h"
#include "ImageUI.h"
#include "TextUI.h"
#include <memory>

namespace Rogalique {

class SettingsState : public EngineCore::GameState {
public:
    SettingsState();
    ~SettingsState() override;

    void Update(float deltaTime) override;
    void Render() override;
    void HandleEvent(const sf::Event& event) override;
    
    static bool musicEnabled;
    static bool mazeEnabled;
    static bool enemiesEnabled;

private:
    void CreateUI();
    void CreateAudioTab();
    void CreateGameplayTab();
    
    void ToggleMusic(bool enable);
    void ToggleEnemies(bool enable);

    std::shared_ptr<UiManager> uiManager;
    std::shared_ptr<ImageUI> background;
    std::shared_ptr<TabsUI> tabsSystem;
    std::shared_ptr<ButtonUI> backButton;
    std::shared_ptr<TextUI> titleText;
};

}

