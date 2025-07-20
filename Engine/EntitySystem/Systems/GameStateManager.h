#pragma once
#include "GameState.h"

namespace EngineCore {
class GameStateManager {
public:
    static GameStateManager* Instance();
    
    void ChangeState(std::shared_ptr<GameState> newState);
    
    void PushState(std::shared_ptr<GameState> state);
    
    void PopState();
        
    void Update(float deltaTime);
    void Render();
    void HandleEvent(const sf::Event& event);

private:
    std::vector<std::shared_ptr<GameState>> states;
};
}