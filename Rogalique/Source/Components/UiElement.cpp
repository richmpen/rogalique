#include "UiElement.h"

#include "AmmoComponent.h"
#include "GameSettings.h"

namespace Rogalique {

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
}

void UiElement::SetScale(sf::Vector2f scale) { sprite.setScale(scale); }

void UiElement::SetColor(sf::Color color) { sprite.setColor(color); }

// HealthBar
HealthBar::HealthBar(const std::string& textureName, sf::IntRect bgRect,
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

void HealthBar::SetHealth(float current, float max) {
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

void HealthBar::Update(float deltaTime) {
    if (!playerGameObject) return;
    auto healthComponent = playerGameObject->GetComponent<HealthComponent>();
    if (!healthComponent) return;
    float current = static_cast<float>(healthComponent->GetHealth());
    float max = 100.0f;
    SetHealth(current, max);
}

void HealthBar::Render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(bar);
}

void HealthBar::SetBarPosition(sf::Vector2f newPosition) {
    healthBarPosition = newPosition;
    SetPosition(newPosition);
}

void HealthBar::SetBarScale(sf::Vector2f newScale) {
    healthBarScale = newScale;
    SetScale(newScale);
}

void HealthBar::SetBarColor(sf::Color newColor) {
    healthBarColor = newColor;
    SetColor(newColor);
}

// ArmorBar
ArmorBar::ArmorBar(const std::string& textureName, sf::IntRect bgRect,
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

void ArmorBar::SetArmor(float current, float max) {
    currentArmor = current;
    maxArmor = max;
    float percent = (max > 0) ? (current / max) : 0.f;
    int newWidth = static_cast<int>(barRectOriginal.width * percent);
    sf::IntRect newRect = barRectOriginal;
    newRect.width = newWidth > 0 ? newWidth : 0;
    bar.setTextureRect(newRect);
}

void ArmorBar::Update(float deltaTime) {
    if (!playerGameObject) return;
    auto armorComponent = playerGameObject->GetComponent<ArmorComponent>();
    if (!armorComponent) return;
    float current = static_cast<float>(armorComponent->GetArmor());
    float max = static_cast<float>(armorComponent->GetMaxArmor());
    SetArmor(current, max);
}

void ArmorBar::Render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(bar);
}
void ArmorBar::SetBarPosition(sf::Vector2f newPosition) {
    armorBarPosition = newPosition;
    SetPosition(newPosition);
}

void ArmorBar::SetBarScale(sf::Vector2f newScale) {
    armorBarScale = newScale;
    SetScale(newScale);
}

void ArmorBar::SetBarColor(sf::Color newColor) {
    armorBarColor = newColor;
    SetColor(newColor);
}

// AmmoBar
AmmoBar::AmmoBar(const std::string& textureName, sf::IntRect bgRect,
                 sf::IntRect barRect, sf::Vector2f FirstTextPosition,
                 sf::Vector2f SecondtTextPosition, sf::Vector2f position,
                 sf::Vector2f barScale, EngineCore::GameObject* player)
    : barRectOriginal(barRect),
      playerGameObject(player),
      ammoBarScale(barScale) {
    font.loadFromFile(SETTINGS.FONTS_PATH + "roboto/Roboto-Medium.ttf");

    const sf::Texture* tex =
        EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName);
    if (tex) {
        background.setTexture(*tex);
        background.setTextureRect(bgRect);
        background.setPosition(position);
        background.setColor(sf::Color(221, 204, 136));
        background.setScale(ammoBarScale);

        bar.setTexture(*tex);
        bar.setTextureRect(barRect);
        bar.setPosition(position);
        bar.setColor(sf::Color(248, 255, 156));
        bar.setScale(ammoBarScale);

        ammoTextFirst.setFont(font);
        ammoTextFirst.setPosition(FirstTextPosition);
        ammoTextFirst.setFillColor(sf::Color(221, 204, 136));
        ammoTextFirst.setCharacterSize(64);
        ammoTextFirst.setStyle(sf::Text::Bold);

        ammoTextSecond.setFont(font);
        ammoTextSecond.setPosition(SecondtTextPosition);
        ammoTextSecond.setFillColor(sf::Color(105, 97, 64));
        ammoTextSecond.setCharacterSize(24);
        ammoTextSecond.setStyle(sf::Text::Italic);
    }
}

void AmmoBar::SetAmmo(float current, float max) {
    currentAmmo = current;
    maxAmmo = max;
    float percent = (max > 0) ? (current / max) : 0.f;
    int newWidth = static_cast<int>(barRectOriginal.width * percent);
    sf::IntRect newRect = barRectOriginal;
    newRect.width = newWidth > 0 ? newWidth : 0;
    bar.setTextureRect(newRect);
}

void AmmoBar::Update(float deltaTime) {
    if (!playerGameObject) return;
    auto ammoComponent = playerGameObject->GetComponent<AmmoComponent>();
    if (!ammoComponent) return;
    float current = static_cast<float>(ammoComponent->GetAmmo());
    float max = static_cast<float>(ammoComponent->GetMaxAmmo());
    int ammoInClip = ammoComponent->GetAmmoInClip();
    SetAmmo(current, max);
    ammoTextFirst.setString(std::to_string(currentAmmo));
    ammoTextSecond.setString(std::to_string(ammoInClip));
}
void AmmoBar::Render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(bar);
    window.draw(ammoTextFirst);
    window.draw(ammoTextSecond);
}
void AmmoBar::SetBarPosition(sf::Vector2f newPosition) {
    ammoBarPosition = newPosition;
    SetPosition(newPosition);
}

void AmmoBar::SetBarScale(sf::Vector2f newScale) {
    ammoBarScale = newScale;
    SetScale(newScale);
}

void AmmoBar::SetBarColor(sf::Color newColor) {
    ammoBarColor = newColor;
    SetColor(newColor);
}

// UiImageElement
UiImageElement::UiImageElement(const std::string& textureName, sf::IntRect rect,
                               sf::Vector2f position)
    : elementRect(rect), elementPosition(position), elementScale(1.0f, 1.0f) {
    SetTextureFromMap(textureName, rect);
    SetPosition(position);
    SetScale(elementScale);
}

void UiImageElement::Update(float deltaTime) {}

void UiImageElement::Render(sf::RenderWindow& window) {
    if (texture) {
        window.draw(sprite);
    }
}

void UiImageElement::SetElement(sf::IntRect newRect) {
    elementRect = newRect;
    sprite.setTextureRect(newRect);
}

void UiImageElement::SetElementPosition(sf::Vector2f newPosition) {
    elementPosition = newPosition;
    SetPosition(newPosition);
}

void UiImageElement::SetElementScale(sf::Vector2f newScale) {
    elementScale = newScale;
    SetScale(newScale);
}

void UiImageElement::SetElementColor(sf::Color newColor) {
    elementColor = newColor;
    SetColor(newColor);
}

}  // namespace Rogalique