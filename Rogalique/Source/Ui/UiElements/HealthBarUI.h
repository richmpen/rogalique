#pragma once
#include "Ui/UiElement.h"


namespace Rogalique {
class HealthBarUI : public UiElement {
   public:
    HealthBarUI(const std::string& textureName, sf::IntRect bgRect,
              sf::IntRect barRect, sf::Vector2f position, sf::Vector2f barScale,
              EngineCore::GameObject* player);
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;

   private:
    void SetHealth(float current, float max);
    sf::Sprite background;
    sf::Sprite bar;
    float currentHealth = 0;
    float maxHealth = 0;
    sf::IntRect barRectOriginal;
    EngineCore::GameObject* playerGameObject = nullptr;
    sf::Vector2f healthBarPosition;
    sf::Vector2f healthBarScale;
    sf::Color healthBarColor;
};
}
