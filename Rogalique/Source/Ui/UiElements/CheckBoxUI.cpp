#include "CheckBoxUI.h"
#include "RenderSystem.h"

namespace Rogalique {

CheckBoxUI::CheckBoxUI(const std::string& text, const sf::Vector2f& position, bool initialValue)
    : text(text), position(position), isChecked(initialValue), isEnabled(true), isHovered(false) {
    
    // Setup checkbox rectangle
    checkBoxRect.setSize(sf::Vector2f(20.f, 20.f));
    checkBoxRect.setPosition(position);
    checkBoxRect.setFillColor(sf::Color::White);
    checkBoxRect.setOutlineColor(sf::Color::Black);
    checkBoxRect.setOutlineThickness(2.0f);
    
    // Setup checkmark rectangle
    checkMarkRect.setSize(sf::Vector2f(20.f - 8, 20.f - 8));
    checkMarkRect.setPosition(position.x + 4, position.y + 4);
    checkMarkRect.setFillColor(sf::Color::Green);
    
    // Setup text label
    labelText = std::make_shared<TextUI>(20, sf::Vector2f(position.x + 30.f, position.y), false);
    labelText->SetText(text, false);
    labelText->SetColor(sf::Color::White);
    
    // Setup bounds for click detection
    bounds = sf::FloatRect(position.x, position.y, 20.f + 30.f + text.length() * 10, 20.f);
}

void CheckBoxUI::Update(float deltaTime) {
    if (labelText) {
        labelText->Update(deltaTime);
    }
    
    // Update colors based on state
    if (!isEnabled) {
        checkBoxRect.setFillColor(sf::Color(128, 128, 128));
        if (labelText) labelText->SetColor(sf::Color(128, 128, 128));
    } else if (isHovered) {
        checkBoxRect.setFillColor(sf::Color(240, 240, 240));
        if (labelText) labelText->SetColor(sf::Color(200, 200, 255));
    } else {
        checkBoxRect.setFillColor(sf::Color::White);
        if (labelText) labelText->SetColor(sf::Color::White);
    }
}

void CheckBoxUI::Render(sf::RenderWindow& window) {
    window.draw(checkBoxRect);
    
    if (isChecked) {
        window.draw(checkMarkRect);
    }
    
    if (labelText) {
        labelText->Render(window);
    }
}

bool CheckBoxUI::HandleEvent(const sf::Event& event) {
    if (!isEnabled) return false;
    
    auto& window = EngineCore::RenderSystem::Instance()->GetMainWindow();
    
    auto oldView = window.getView();
    window.setView(window.getDefaultView());
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    window.setView(oldView);
    
    isHovered = bounds.contains(mousePos);
    
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && isHovered) {
            SetChecked(!isChecked);
            if (onValueChanged) {
                onValueChanged(isChecked);
            }
            return true;
        }
    }
    
    return false;
}

void CheckBoxUI::SetChecked(bool checked) {
    isChecked = checked;
}

} 