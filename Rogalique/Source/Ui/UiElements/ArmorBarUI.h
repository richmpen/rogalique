#pragma once

#include "GameSettings.h"
#include "TextUI.h"
namespace Rogalique {
class ArmorBarUI : public UiElement {
   public:
    ArmorBarUI(const std::string& textureName, sf::IntRect bgRect,
             sf::IntRect barRect, sf::Vector2f position, sf::Vector2f barScale,
             EngineCore::GameObject* player);
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void SetBarPosition(sf::Vector2f newPosition);
    void SetBarScale(sf::Vector2f newScale);
    void SetBarColor(sf::Color newColor);

   private:
    void SetArmor(float current, float max);
    sf::Sprite background;
    sf::Sprite bar;
    float currentArmor = 0;
    float maxArmor = 0;
    sf::IntRect barRectOriginal;
    EngineCore::GameObject* playerGameObject = nullptr;
    sf::Vector2f armorBarPosition;
    sf::Vector2f armorBarScale;
    sf::Color armorBarColor;
};
}
