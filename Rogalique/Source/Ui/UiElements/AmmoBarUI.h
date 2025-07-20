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
    void SetBarPosition(sf::Vector2f newPosition);
    void SetBarScale(sf::Vector2f newScale);
    void SetBarColor(sf::Color newColor);

   private:
    void SetAmmo(float current, float max);

    sf::Sprite background;
    sf::Sprite bar;
    std::shared_ptr<TextUI> firstText;
    std::shared_ptr<TextUI> secondText;
    int currentAmmo = 0;
    int maxAmmo = 0;

    EngineCore::GameObject* playerGameObject = nullptr;
    sf::IntRect barRectOriginal;
    sf::Vector2f ammoBarPosition;
    sf::Vector2f ammoBarScale;
    sf::Color ammoBarColor;
};
}
