#pragma once
#include "Item.h"

namespace Rogalique {

    class AmmoItem : public Item {
    public:
        AmmoItem(ItemType type, int count, sf::Vector2f position, const std::string& textureName, int ammoAmount = 30);
        void Use(EngineCore::GameObject* player) override;

    private:
        int ammoAmount;
    };

}
