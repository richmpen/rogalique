#pragma once
#include "UiElement.h"
#include "TextUI.h"
#include <functional>
#include <SFML/Graphics.hpp>

namespace Rogalique {
class CheckBoxUI : public UiElement {
public:
    CheckBoxUI(const std::string& text, 
               const sf::Vector2f& position, 
               bool initialValue = false);
    
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    bool HandleEvent(const sf::Event& event) override;
    
    void SetChecked(bool checked);
    bool IsChecked() const { return isChecked; }
    
    void SetOnValueChanged(std::function<void(bool)> callback) { onValueChanged = callback; }
    
    void SetEnabled(bool enabled) { isEnabled = enabled; }
    bool IsEnabled() const { return isEnabled; }

private:
    std::shared_ptr<TextUI> labelText;
    std::function<void(bool)> onValueChanged;
    
    sf::RectangleShape checkBoxRect;
    sf::RectangleShape checkMarkRect;
    sf::FloatRect bounds;
    
    std::string text;
    bool isChecked;
    bool isEnabled;
    bool isHovered;
    
    sf::Vector2f position;
    
    
};
} 