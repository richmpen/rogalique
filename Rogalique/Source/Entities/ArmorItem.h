#pragma once
#include "Item.h"

namespace Rogalique {

    class ArmorItem : public Item {
    public:
        ArmorItem(ItemType type, int count, sf::Vector2f position, const std::string& textureName, int armorAmount = 30);
        void Use(EngineCore::GameObject* player) override;

    private:
        int armorAmount;
    };

}
