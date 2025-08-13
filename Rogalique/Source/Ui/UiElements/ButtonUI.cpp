#include "ButtonUI.h"

#include "RenderSystem.h"
#include "ResourceSystem.h"

namespace Rogalique {

ButtonUI::ButtonUI(const std::string& text, const std::string& textureName,
                   sf::IntRect rect, sf::Vector2f position, sf::Vector2f size,
                   sf::Color color)
    : text(text),
      rect(rect),
      position(position),
      scale(1.0f, 1.0f),
      color(color) {
    SetTextureFromMap(textureName, rect);
    UiElement::SetPosition(position);
    UiElement::SetColor(color);
    ButtonUI::SetScale(size);

    buttonText = std::make_shared<TextUI>(
        24, sf::Vector2f(position.x, position.y - 5), false);
    buttonText->SetText(text, true);
    buttonText->SetColor(sf::Color::White);

    bounds = sprite.getGlobalBounds();
}

void ButtonUI::Update(float deltaTime) {
    bounds = sprite.getGlobalBounds();

    if (!isEnabled) {
        sprite.setColor(disabledColor);
        return;
    }

    if (isSelected) {
        sprite.setColor(color);
        return;
    }

    if (isPressed) {
        sprite.setColor(pressColor);
    } else if (isHovered) {
        sprite.setColor(hoverColor);
    } else {
        sprite.setColor(color);
    }
}

void ButtonUI::Render(sf::RenderWindow& window) {
    window.draw(sprite);

    if (buttonText) {
        buttonText->Render(window);
    }
}

bool ButtonUI::HandleEvent(const sf::Event& event) {
    if (!isEnabled || !isActive) return false;

    auto& window = EngineCore::RenderSystem::Instance()->GetMainWindow();

    auto oldView = window.getView();
    window.setView(window.getDefaultView());
    sf::Vector2f mousePos =
        window.mapPixelToCoords(sf::Mouse::getPosition(window));
    window.setView(oldView);

    bool wasHovered = isHovered;
    isHovered = bounds.contains(mousePos);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && isHovered) {
            isPressed = true;
            return true;
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left && isPressed) {
            isPressed = false;
            if (isHovered && onClick) {
                onClick();
            }
            return true;
        }
    }

    return false;
}

void ButtonUI::SetText(const std::string& text, bool setOrigin) {
    if (buttonText) {
        buttonText->SetText(text, setOrigin);
    }
}

void ButtonUI::SetScale(sf::Vector2f scale) {
    sf::Vector2f textureSize(static_cast<float>(rect.width),
                             static_cast<float>(rect.height));
    sf::Vector2f size(scale.x / textureSize.x, scale.y / textureSize.y);
    UiElement::SetScale(size);
}

void ButtonUI::SetColor(sf::Color newColor) {
    color = newColor;
    UiElement::SetColor(newColor);
}

}  // namespace Rogalique