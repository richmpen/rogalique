#include "HealthBarUI.h"

#include "HealthComponent.h"

namespace Rogalique {
HealthBarUI::HealthBarUI(const std::string& textureName, sf::IntRect bgRect,
                         sf::IntRect barRect, sf::Vector2f position,
                         sf::Vector2f barScale, EngineCore::GameObject* player)
    : barRectOriginal(barRect),
      playerGameObject(player),
      healthBarScale(barScale) {
    const sf::Texture* tex =
        EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName);
    if (tex) {
        background.setTexture(*tex);
        background.setTextureRect(bgRect);
        background.setPosition(position);
        background.setColor(sf::Color(87, 157, 194));
        background.setScale(healthBarScale);

        bar.setTexture(*tex);
        bar.setTextureRect(barRect);
        bar.setPosition(position);
        bar.setColor(sf::Color(129, 235, 254));
        bar.setScale(healthBarScale);
    }
    maxHealth = static_cast<float>(
        player->GetComponent<HealthComponent>()->GetMaxHealth());
}

void HealthBarUI::SetHealth(float current, float max) {
    currentHealth = current;
    maxHealth = max;
    float percent = (max > 0) ? (current / max) : 0.f;
    int newWidth = static_cast<int>(barRectOriginal.width * percent);
    sf::IntRect newRect = barRectOriginal;
    newRect.width = newWidth > 0 ? newWidth : 0;
    bar.setTextureRect(newRect);

    if (percent > 0.6f) {
        bar.setColor(sf::Color(22, 124, 255));
    } else if (percent > 0.3f) {
        bar.setColor(sf::Color(127, 58, 13));
    } else {
        bar.setColor(sf::Color(166, 0, 0));
    }
}

void HealthBarUI::Update(float deltaTime) {
    if (!playerGameObject) return;
    auto healthComponent = playerGameObject->GetComponent<HealthComponent>();
    if (!healthComponent) return;
    float current = static_cast<float>(healthComponent->GetHealth());
    float max = static_cast<float>(healthComponent->GetMaxHealth());
    SetHealth(current, max);
}

void HealthBarUI::Render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(bar);
}

}  // namespace Rogalique