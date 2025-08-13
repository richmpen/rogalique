#include "UiElement.h"

namespace Rogalique {
void UiElement::SetTexture(const std::string textureName) {
    texture =
        EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName);
    if (texture) {
        sprite.setTexture(*texture);
    }
}

void UiElement::SetTextureFromMap(const std::string& textureName,
                                  sf::IntRect rect) {
    texture =
        EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName);
    if (texture) {
        sprite.setTexture(*texture);
        sprite.setTextureRect(rect);
    }
}

void UiElement::SetPosition(sf::Vector2f position) {
    sprite.setPosition(position);
    bounds = sprite.getGlobalBounds();
}

void UiElement::SetScale(sf::Vector2f scale) {
    sprite.setScale(scale);
    bounds = sprite.getGlobalBounds();
}

sf::Vector2f UiElement::GetScale() { return sprite.getScale(); }

void UiElement::SetColor(sf::Color color) { sprite.setColor(color); }

void UiElement::SetCenterOrigin() {
    sf::FloatRect rc = sprite.getLocalBounds();
    sprite.setOrigin(rc.width / 2, rc.height / 2);
    bounds = sprite.getGlobalBounds();
}
}  // namespace Rogalique