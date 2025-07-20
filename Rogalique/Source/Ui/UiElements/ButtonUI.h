#pragma once
#include "UiElement.h"
#include <functional>
#include "GameSettings.h"
#include "TextUI.h"
#include <SFML/Graphics.hpp>

namespace Rogalique {
class ButtonUI : public UiElement {
public:

    ButtonUI(const std::string& text, const std::string& textureName, sf::IntRect rect, sf::Vector2f position, sf::Vector2f size, sf::Color color);
        
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    bool HandleEvent(const sf::Event& event) override;
        
    void SetOnClick(std::function<void()> callback) { onClick = callback; }
    void SetText(const std::string& text, bool setOrigin);
    void SetEnabled(bool enabled) { isEnabled = enabled; }
    

    void SetElementPosition(sf::Vector2f newPosition);
    void SetElementScale(sf::Vector2f newScale);
    void SetElementSize(sf::Vector2f size);
    void SetElementColor(sf::Color newColor);
    void SetElementOriginCenter();
        
private:
    std::function<void()> onClick;
    std::shared_ptr<TextUI> buttonText;
        
    
    sf::Sprite background;
    
    
    
    bool originInCenter = true;
    sf::Vector2f elementPosition;
    sf::Vector2f elementScale = sf::Vector2f(1.0f, 1.0f);
    sf::IntRect elementRect;
    std::string text;
        
    bool isHovered = false;
    bool isPressed = false;
    bool isEnabled = true;
    
    sf::Color color;
    sf::Color hoverColor = sf::Color(70, 70, 70);
    sf::Color pressColor = sf::Color(30, 30, 30);
    sf::Color disabledColor = sf::Color(30, 30, 30, 128);
};
}