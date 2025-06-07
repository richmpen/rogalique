#pragma once
#include "GameStateData.h"
#include "Menu.h"
#include "ScoreSystem.h"

#include "SFML/Graphics.hpp"

namespace Rogalique {
class Game;

class GameStateGameWin : public GameStateData {
   public:
    void Init() override;
    void Shutdown() override;
    void Control(const sf::Event& event) override;
    void Update(float timeDelta) override;
    void Draw(sf::RenderWindow& window) override;

   private:
    sf::Font font;

    float timeSinceGameWin = 0.f;

    sf::RectangleShape background;
    sf::Text gameWinText;
    sf::Text hintText;
    sf::Text scoreTotalText;
    std::vector<sf::Text> recordsTableTexts;
    Menu menu;
};

}  // namespace Rogalique
