#pragma once
#include "GameStateData.h"

#include <SFML/Graphics.hpp>
#include <vector>

namespace Rogalique {
class Game;

class GameStateRecords : public GameStateData {
   public:
    void Init() override;
    void Shutdown() override;
    void Control(const sf::Event& event) override;
    void Update(float timeDelta) override;
    void Draw(sf::RenderWindow& window) override;

   private:
    sf::Font font;

    sf::Text titleText;
    std::vector<sf::Text> tableTexts;
    sf::Text hintText;
};

}  // namespace Rogalique
