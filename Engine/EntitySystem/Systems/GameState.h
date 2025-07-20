#pragma once
#include <SFML/Graphics.hpp>

namespace EngineCore {
class GameState {
public:
    virtual ~GameState() = default;
        
    virtual void Update(float deltaTime) = 0;
    virtual void Render() = 0;
    virtual void HandleEvent(const sf::Event& event) {}
        
protected:
    
};
};