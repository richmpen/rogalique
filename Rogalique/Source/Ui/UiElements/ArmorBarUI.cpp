#include "ArmorBarUI.h"

#include "ArmorComponent.h"

namespace Rogalique {
ArmorBarUI::ArmorBarUI(const std::string& textureName, sf::IntRect bgRect,
                   sf::IntRect barRect, sf::Vector2f position,
                   sf::Vector2f barScale, EngineCore::GameObject* player)
    : barRectOriginal(barRect),
      playerGameObject(player),
      armorBarScale(barScale) {
    const sf::Texture* tex =
        EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName);
    if (tex) {
        background.setTexture(*tex);
        background.setTextureRect(bgRect);
        background.setPosition(position);
        background.setColor(sf::Color(8, 124, 2));
        background.setScale(armorBarScale);

        bar.setTexture(*tex);
        bar.setTextureRect(barRect);
        bar.setPosition(position);
        bar.setColor(sf::Color(15, 191, 6));
        bar.setScale(armorBarScale);
    }
}

void ArmorBarUI::SetArmor(float current, float max) {
    currentArmor = current;
    maxArmor = max;
    float percent = (max > 0) ? (current / max) : 0.f;
    int newWidth = static_cast<int>(barRectOriginal.width * percent);
    sf::IntRect newRect = barRectOriginal;
    newRect.width = newWidth > 0 ? newWidth : 0;
    bar.setTextureRect(newRect);
}

void ArmorBarUI::Update(float deltaTime) {
    if (!playerGameObject) return;
    auto armorComponent = playerGameObject->GetComponent<ArmorComponent>();
    if (!armorComponent) return;
    float current = static_cast<float>(armorComponent->GetArmor());
    float max = static_cast<float>(armorComponent->GetMaxArmor());
    SetArmor(current, max);
}

void ArmorBarUI::Render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(bar);
}
void ArmorBarUI::SetBarPosition(sf::Vector2f newPosition) {
    armorBarPosition = newPosition;
    SetPosition(newPosition);
}

void ArmorBarUI::SetBarScale(sf::Vector2f newScale) {
    armorBarScale = newScale;
    SetScale(newScale);
}

void ArmorBarUI::SetBarColor(sf::Color newColor) {
    armorBarColor = newColor;
    SetColor(newColor);
}
}