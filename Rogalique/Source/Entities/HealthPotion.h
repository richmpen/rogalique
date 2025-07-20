#pragma once
#include "Item.h"
#include "ItemType.h"

namespace Rogalique {
    
    class HealthPotion : public Item {
    public:
        HealthPotion(ItemType type, int count, sf::Vector2f position, const std::string& textureName, int healAmount = 50);
        void Use(EngineCore::GameObject* player) override;

    private:
        int healAmount;
    };
    
} 