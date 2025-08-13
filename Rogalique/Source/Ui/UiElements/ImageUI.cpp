#include "ImageUI.h"

#include "RenderSystem.h"

namespace Rogalique {

ImageUI::ImageUI(const std::string& textureName, sf::IntRect rect,
                 sf::Vector2f position)
    : rect(rect), position(position), scale(1.0f, 1.0f), originInCenter(true) {
    SetTextureFromMap(textureName, rect);
    UiElement::SetPosition(position);
    UiElement::SetScale(scale);

    bounds = sprite.getGlobalBounds();
}

ImageUI::ImageUI(const std::string& textureName, sf::Vector2f size,
                 sf::Vector2f position)
    : position(position), scale(size.x, size.y), originInCenter(true) {
    SetTexture(textureName);
    UiElement::SetPosition(position);
    UiElement::SetScale(scale);
    if (originInCenter) {
        UiElement::SetCenterOrigin();
    }

    bounds = sprite.getGlobalBounds();
}

void ImageUI::Update(float deltaTime) { bounds = sprite.getGlobalBounds(); }

void ImageUI::Render(sf::RenderWindow& window) {
    if (texture) {
        window.draw(sprite);
    }
}

void ImageUI::SetElement(sf::IntRect newRect) {
    rect = newRect;
    sprite.setTextureRect(newRect);
    bounds = sprite.getGlobalBounds();
}
}  // namespace Rogalique
