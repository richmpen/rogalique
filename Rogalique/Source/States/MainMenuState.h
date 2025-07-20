#pragma once
#include "GameState.h"
#include "UiManager.h"
#include "ButtonUI.h"
#include "ImageUI.h"

namespace Rogalique {
class MainMenuState : public EngineCore::GameState {
public:
    MainMenuState();
    
    void Update(float deltaTime) override;
    void Render() override;
    void HandleEvent(const sf::Event& event) override;
        
private:
    void CreateUI();
        
    std::shared_ptr<UiManager> uiManager;
    std::shared_ptr<TextUI> titleText;
    std::shared_ptr<ImageUI> logo;
    std::shared_ptr<ButtonUI> playButton;
    std::shared_ptr<ButtonUI> continueButton;
    std::shared_ptr<ButtonUI> settingsButton;
    std::shared_ptr<ButtonUI> exitButton;
    std::shared_ptr<ImageUI> background;
};
}