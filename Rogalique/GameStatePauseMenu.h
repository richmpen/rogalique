#pragma once
#include "GameStateData.h"
#include "Menu.h"

#include <SFML/Graphics.hpp>

namespace Rogalique {
class Game;

class GameStatePauseMenu : public GameStateData {
   public:
    void Init() override;
    void Shutdown() override;
    void Control(const sf::Event& event) override;
    void Update(float timeDelta) override;
    void Draw(sf::RenderWindow& window) override;

   private:
    sf::Font font;

    sf::RectangleShape background;
    sf::Text titleText;

    Menu menu;
};

}  // namespace Rogalique
