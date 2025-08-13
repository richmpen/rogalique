#pragma once
#include "ButtonUI.h"
#include "GameState.h"
#include "ButtonUI.h"
#include "DeveloperLevel.h"
#include "ImageUI.h"
#include "PlayState.h"
#include "UiManager.h"

namespace Rogalique {
class PauseState : public EngineCore::GameState {
    public:
    PauseState();
    ~PauseState() override;

    void Update(float deltaTime) override;
    void Render() override;
    void HandleEvent(const sf::Event& event) override;
    private:
    void CreateUI();
    std::unique_ptr<DeveloperLevel> currentLevel;
    std::shared_ptr<UiManager> uiManager;
    std::shared_ptr<ImageUI> pauseBackground;
    std::shared_ptr<ButtonUI> continueButton;
    std::shared_ptr<ButtonUI> backToMenuButton;
    std::shared_ptr<PlayState> pause;
};
}