#include "HealthPotion.h"
#include "GameWorld.h"
#include "HealthComponent.h"
#include "Logger.h"

namespace Rogalique {
    
    HealthPotion::HealthPotion(ItemType type, int count, sf::Vector2f position, const std::string& textureName, int healAmount) 
        : Item(type, count, position, textureName), healAmount(healAmount) {
    }
    
    void HealthPotion::Use(EngineCore::GameObject* player) {
        if (!player) return;
        
        auto healthComponent = player->GetComponent<HealthComponent>();
        if (healthComponent) {
            int currentHealth = healthComponent->GetHealth();
            int maxHealth = healthComponent->GetMaxHealth();
            int newHealth = std::min(currentHealth + healAmount, maxHealth);
            healthComponent->SetHealth(newHealth);
        }
    }
    
} 