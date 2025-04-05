#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "Block.h"
#include "LevelLoader.h"

namespace Rogalique
{
    struct LevelState {
        sf::Vector2f platePosition;
        sf::Vector2f ballPosition;
        std::vector<std::shared_ptr<Block>> blocks;
        int score;
        std::vector<std::pair<BonusType, sf::Vector2f>> bonuses;
    };
}