#pragma once
#include "ButtonUI.h"
#include "DeveloperLevel.h"
#include "GameState.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "UiManager.h"

namespace Rogalique {
class GameOverState : public EngineCore::GameState {
   public:
    GameOverState();
    ~GameOverState() override;

    void Update(float deltaTime) override;
    void Render() override;
    void HandleEvent(const sf::Event& event) override;

   private:
    void CreateUI();

    std::shared_ptr<UiManager> uiManager;
    std::shared_ptr<ImageUI> background;
    std::shared_ptr<TextUI> titleText;
    std::shared_ptr<ButtonUI> restartButton;
    std::shared_ptr<ButtonUI> backToMenuButton;
};
}  // namespace Rogalique
