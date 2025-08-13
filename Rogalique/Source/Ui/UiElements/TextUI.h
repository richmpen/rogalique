#pragma once
#include "Ui/UiElement.h"


namespace Rogalique {

class TextUI : public UiElement {
   public:
    TextUI(int size, sf::Vector2f position, bool bold);

    void Update(float deltaTime) override {}
    void Render(sf::RenderWindow& window) override;

    void SetText(const std::string& newText, bool setOrigin);
    void SetTextPosition(sf::Vector2f newPosition);
    void SetColor(sf::Color newColor) override;
    void SetStyle(sf::Text::Style style);
    void SetCenterOrigin() override;
    const sf::Font* GetFirstFont();
    const sf::Font* GetSecondFont();
    

private:
    const sf::Font* firstFont;
    const sf::Font* secondFont;
    sf::Text text;
    
};
}
