#include "WeaponItem.h"
#include "FightComponent.h"
#include "ItemType.h"
#include "Logger.h"

namespace Rogalique {

    WeaponItem::WeaponItem(ItemType type, int count, sf::Vector2f position, const std::string& textureName, int damageBonus) 
        : Item(ItemType::WEAPON, count, position, textureName), damageBonus(damageBonus) {
    }
    
    void WeaponItem::Use(EngineCore::GameObject* player) {
        if (!player) return;
        
        auto fightComponent = player->GetComponent<FightComponent>();
        if (fightComponent) {
            int currentDamage = fightComponent->GetDamage();
            int newDamage = currentDamage + damageBonus;
            fightComponent->SetDamage(newDamage);
        }
    }

}