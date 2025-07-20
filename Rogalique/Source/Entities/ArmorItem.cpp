#include "ArmorItem.h"
#include "ArmorComponent.h"
#include "ItemType.h"
#include "Logger.h"

namespace Rogalique {

    ArmorItem::ArmorItem(ItemType type, int count, sf::Vector2f position, const std::string& textureName, int armorAmount) 
        : Item(ItemType::ARMOR, count, position, textureName), armorAmount(armorAmount) {
    }
    
    void ArmorItem::Use(EngineCore::GameObject* player) {
        if (!player) return;
        
        auto armorComponent = player->GetComponent<ArmorComponent>();
        if (armorComponent) {
            int currentArmor = armorComponent->GetArmor();
            int maxArmor = armorComponent->GetMaxArmor();
            int newArmor = std::min(currentArmor + armorAmount, maxArmor);
            armorComponent->SetArmor(newArmor);
            LOG_INFO("Player used Armor Item! Armor: " << currentArmor << " -> " << newArmor)
        }
    }

}