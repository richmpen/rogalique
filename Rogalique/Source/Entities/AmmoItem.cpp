#include "AmmoItem.h"
#include "AmmoComponent.h"
#include "ItemType.h"
#include "Logger.h"

namespace Rogalique {

    AmmoItem::AmmoItem(ItemType type, int count, sf::Vector2f position, const std::string& textureName, int ammoAmount) 
        : Item(ItemType::AMMO, count, position, textureName), ammoAmount(ammoAmount) {
    }
    
    void AmmoItem::Use(EngineCore::GameObject* player) {
        if (!player) return;
        
        auto ammoComponent = player->GetComponent<AmmoComponent>();
        if (ammoComponent) {
            int currentAmmo = ammoComponent->GetAmmo();
            int maxAmmo = ammoComponent->GetMaxAmmo();
            int newAmmo = std::min(currentAmmo + ammoAmount, maxAmmo);
            ammoComponent->AddAmmo(ammoAmount);
            LOG_INFO("Player used Ammo Item! Ammo: " << currentAmmo << " -> " << newAmmo)
        }
    }

}