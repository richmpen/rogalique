#include "CheckBoxUI.h"

#include "RenderSystem.h"

namespace Rogalique {

CheckBoxUI::CheckBoxUI(const std::string& text, const sf::Vector2f& position,
                       bool initialValue)
    : text(text),
      position(position),
      isChecked(initialValue),
      isEnabled(true),
      isHovered(false) {
    checkBoxBackground = std::make_shared<ImageUI>(
        "UiMap2", sf::IntRect(1649, 1524, 1216, 182),
        sf::Vector2f(position.x + 180, position.y + 10));
    checkBoxBackground->SetCenterOrigin();
    checkBoxBackground->SetScale(sf::Vector2f(0.4f, 0.25f));
    checkBoxBackground->SetColor(sf::Color::Green);

    checkBoxRect.setSize(sf::Vector2f(20.f, 20.f));
    checkBoxRect.setPosition(position);
    checkBoxRect.setFillColor(sf::Color::White);
    checkBoxRect.setOutlineColor(sf::Color::Black);
    checkBoxRect.setOutlineThickness(2.0f);

    checkMarkRect.setSize(sf::Vector2f(20.f - 8, 20.f - 8));
    checkMarkRect.setPosition(position.x + 4, position.y + 4);
    checkMarkRect.setFillColor(sf::Color::Green);

    labelText = std::make_shared<TextUI>(
        28, sf::Vector2f(position.x + 35.f, position.y - 7.f), true);
    labelText->SetText(text, false);
    labelText->SetColor(sf::Color::White);

    bounds = sf::FloatRect(position.x, position.y,
                           20.f + 30.f + text.length() * 20, 20.f);
}

void CheckBoxUI::Update(float deltaTime) {
    if (labelText) {
        labelText->Update(deltaTime);
    }

    // Update colors
    if (!isEnabled) {
        checkBoxRect.setFillColor(sf::Color(128, 128, 128));
        if (labelText) labelText->SetColor(sf::Color(128, 128, 128));
    } else if (isHovered) {
        checkBoxRect.setFillColor(sf::Color(240, 240, 240));
        if (labelText) labelText->SetColor(sf::Color(38, 153, 38));
    } else {
        checkBoxRect.setFillColor(sf::Color::White);
        if (labelText) labelText->SetColor(sf::Color::White);
    }
}

void CheckBoxUI::Render(sf::RenderWindow& window) {
    if (checkBoxBackground) {
        checkBoxBackground->Render(window);
    }

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
    sf::Vector2f mousePos =
        window.mapPixelToCoords(sf::Mouse::getPosition(window));
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

void CheckBoxUI::SetChecked(bool checked) { isChecked = checked; }

}  // namespace Rogalique