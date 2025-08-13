#pragma once
#include "Ui/UiElement.h"

namespace Rogalique {

class ImageUI : public UiElement {
   public:
    ImageUI(const std::string& textureName, sf::IntRect rect,
            sf::Vector2f position);
    ImageUI(const std::string& textureName, sf::Vector2f size,
            sf::Vector2f position);
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;

    void SetElement(sf::IntRect newRect);

   private:
    bool originInCenter;
    sf::IntRect rect;
    sf::Vector2f position;
    sf::Vector2f scale;
    sf::Color color;
};

}  // namespace Rogalique
