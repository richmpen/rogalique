#include "pch.h"
#include "GameStateManager.h"


namespace EngineCore {
GameStateManager* GameStateManager::Instance() {
    static GameStateManager instance;
    return &instance;
}
    
void GameStateManager::ChangeState(std::shared_ptr<GameState> newState) {
    while (!states.empty()) {
        states.pop_back();
    }
    PushState(newState);
}
    
void GameStateManager::PushState(std::shared_ptr<GameState> state) {
    states.push_back(state);
    LOG_INFO("Pushed state, stack size: " << states.size());
}
    
void GameStateManager::PopState() {
    if (!states.empty()) {
        states.pop_back();
        LOG_INFO("Popped state, stack size: " << states.size());
    }
}
    
void GameStateManager::Update(float deltaTime) {
    for (size_t i = 0; i < states.size(); ++i) {
        if (i == states.size() - 1) {
            states[i]->Update(deltaTime);
        }
    }
}
    
void GameStateManager::Render() {
    
    if (states.empty()) {return;};
    int startIndex = states.size() - 1;
    for (int i = startIndex; i < (int)states.size(); ++i) {
        states[i]->Render();
    }
}
    
void GameStateManager::HandleEvent(const sf::Event& event) {

    if (!states.empty()) {
        states.back()->HandleEvent(event);
    }
}
}