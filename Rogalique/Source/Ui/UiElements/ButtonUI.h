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
    void SetSelected(bool selected) { isSelected = selected; }
    void SetScale(sf::Vector2f scale) override;
    void SetColor(sf::Color newColor) override;

private:
    std::function<void()> onClick;
    std::shared_ptr<TextUI> buttonText;
    
    sf::Sprite background;
    
    sf::Vector2f position;
    sf::Vector2f scale = sf::Vector2f(1.0f, 1.0f);
    sf::IntRect rect;
    std::string text;

    bool isHovered = false;
    bool isPressed = false;
    bool isEnabled = true;
    bool isActive = true;
    bool isSelected = false;

    sf::Color color;
    sf::Color hoverColor = sf::Color(40, 150, 40);
    sf::Color pressColor = sf::Color(30, 30, 30);
    sf::Color disabledColor = sf::Color(30, 30, 30, 128);
};
}