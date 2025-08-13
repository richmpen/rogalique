#include "ArmorBarUI.h"

#include "ArmorComponent.h"

namespace Rogalique {
ArmorBarUI::ArmorBarUI(const std::string& textureName, sf::IntRect bgRect,
                   sf::IntRect barRect, sf::Vector2f position,
                   sf::Vector2f barScale, EngineCore::GameObject* player)
    : rect(barRect),
      playerGameObject(player),
      scale(barScale) {
    const sf::Texture* tex =
        EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName);
    if (tex) {
        background.setTexture(*tex);
        background.setTextureRect(bgRect);
        background.setPosition(position);
        background.setColor(sf::Color(8, 124, 2));
        background.setScale(scale);

        bar.setTexture(*tex);
        bar.setTextureRect(barRect);
        bar.setPosition(position);
        bar.setColor(sf::Color(15, 191, 6));
        bar.setScale(scale);
    }
}

void ArmorBarUI::SetArmor(float current, float max) {
    currentArmor = current;
    maxArmor = max;
    float percent = (max > 0) ? (current / max) : 0.f;
    int newWidth = static_cast<int>(rect.width * percent);
    sf::IntRect newRect = rect;
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
}