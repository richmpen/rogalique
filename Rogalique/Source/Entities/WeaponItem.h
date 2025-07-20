#pragma once
#include "Item.h"

namespace Rogalique {

    class WeaponItem : public Item {
    public:
        WeaponItem(ItemType type, int count, sf::Vector2f position, const std::string& textureName, int damageBonus = 10);
        void Use(EngineCore::GameObject* player) override;

    private:
        int damageBonus;
    };

}
