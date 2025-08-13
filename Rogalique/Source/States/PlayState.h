#pragma once
#include "DeveloperLevel.h"
#include "GameState.h"
#include "UiManager.h"
#include "InventorySystem.h"
#include <memory>

namespace Rogalique {
class PlayState : public EngineCore::GameState {
public:
    PlayState();

    void Update(float deltaTime) override;
    void Render() override;
    void HandleEvent(const sf::Event& event) override;

    void PauseGame();
    void UnpauseGame();
    void TogglePause();
    bool IsPaused() const { return isPaused; }
    
private:
    void CheckGameStates();
    
    std::unique_ptr<DeveloperLevel> currentLevel;
    UiManager* uiManager = nullptr;
    EngineCore::GameObject* gameObject = nullptr;
    bool isPaused = false;
};
}