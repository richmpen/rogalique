#pragma once

#include "GameSettings.h"
#include "TextUI.h"

namespace Rogalique {
class AmmoBarUI : public UiElement {
   public:
    AmmoBarUI(const std::string& textureName, sf::IntRect bgRect,
              sf::IntRect barRect, std::shared_ptr<TextUI> firstText,
              std::shared_ptr<TextUI> secondText, sf::Vector2f position,
              sf::Vector2f barScale, EngineCore::GameObject* player);
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;

   private:
    void SetAmmo(float current, float max);

    sf::Sprite background;
    sf::Sprite bar;
    std::shared_ptr<TextUI> firstText;
    std::shared_ptr<TextUI> secondText;
    int currentAmmo = 0;
    int maxAmmo = 0;

    EngineCore::GameObject* playerGameObject = nullptr;
    sf::IntRect rect;
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Color color;
};
}  // namespace Rogalique
