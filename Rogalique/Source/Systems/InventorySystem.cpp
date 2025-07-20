#include "InventorySystem.h"

#include "CameraComponent.h"
#include "GameSettings.h"
#include "GameWorld.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "AmmoComponent.h"
#include "Item.h"
#include "ItemType.h"
#include "Logger.h"
#include <algorithm>
#include <vector>

namespace Rogalique {

InventorySystem* InventorySystem::Instance() {
    static InventorySystem inventorySystem;
    if (inventorySystem.equippedItems.empty()) {
        inventorySystem.equippedItems.resize(SETTINGS.EQUIPMENT_SLOTS);
    }
    return &inventorySystem;
}

// Handle item collision with player
void InventorySystem::ItemCollision(EngineCore::GameObject* itemGameObject, ItemType itemType, int itemCount, const std::string& textureName){
    auto collider = itemGameObject->GetComponent<EngineCore::SpriteColliderComponent>();
    if (!collider) {
        LOG_ERROR("No collider component found!")
        return;
    }

    std::string textureNameCopy = textureName;
    ItemType itemTypeCopy = itemType;
    int itemCountCopy = itemCount;

    static std::vector<EngineCore::GameObject*> processedItems;
    
    collider->SubscribeCollision([itemGameObject, itemTypeCopy, itemCountCopy, textureNameCopy, collider](EngineCore::Collision collision) {
        for (auto* processed : processedItems) {
            if (processed == itemGameObject) {
                return;
            }
        }
         
        EngineCore::ColliderComponent* otherCollider =
            (collision.GetFirst() == collider) ? collision.GetSecond()
                                               : collision.GetFirst();
        
        if (!otherCollider) {
            LOG_ERROR("INVENTORY: Other collider is null!")
            return;
        }
        
        EngineCore::GameObject* otherObject = otherCollider->GetGameObject();
        if (!otherObject) {
            LOG_ERROR("INVENTORY: Other game object is null!")
            return;
        }

        if (otherObject->GetComponent<EngineCore::CameraComponent>() != nullptr) {
            processedItems.push_back(itemGameObject);
            InventorySystem::Instance()->AddItemToInventory(itemTypeCopy, itemCountCopy, textureNameCopy);
            
            if (itemGameObject != nullptr) {
                EngineCore::GameWorld::Instance()->DestroyGameObject(itemGameObject);
            }
            else {
                LOG_ERROR("Cannot delete - itemGameObject is null!")
            }
        }
    });
}

void InventorySystem::AddItemToInventory(ItemType type, int count, const std::string& textureName) {
    if (inventory.size() >= SETTINGS.MAX_INVENTORY_SIZE) {
        LOG_ERROR("Inventory full! Cannot add item: " << textureName);
        return;
    }
    
    inventory.emplace_back(std::make_unique<Item>(type, count, sf::Vector2f(0, 0), textureName));
}

void InventorySystem::Update(float deltaTime) {}
void InventorySystem::Render() {}

bool InventorySystem::EquipItem(int slotIndex, int inventoryIndex) {
    if (slotIndex < 0 || slotIndex >= SETTINGS.EQUIPMENT_SLOTS) {
        LOG_ERROR("Invalid equipment slot index: " << slotIndex);
        return false;
    }
    
    if (inventoryIndex < 0 || inventoryIndex >= inventory.size()) {
        LOG_ERROR("Invalid inventory index: " << inventoryIndex);
        return false;
    }
    
    if (!IsSlotEmpty(slotIndex)) {
        UnequipItem(slotIndex);
    }
    
    equippedItems[slotIndex] = std::move(inventory[inventoryIndex]);
    inventory[inventoryIndex] = nullptr;
    inventory.erase(std::remove(inventory.begin(), inventory.end(), nullptr), inventory.end());
    
    return true;
}

bool InventorySystem::UnequipItem(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= SETTINGS.EQUIPMENT_SLOTS || IsSlotEmpty(slotIndex)) {
        LOG_ERROR("Cannot unequip from slot " << slotIndex << " - invalid slot or empty");
        return false;
    }
    
    if (inventory.size() >= SETTINGS.MAX_INVENTORY_SIZE) {
        LOG_ERROR("Cannot unequip item - inventory is full! (size: " << inventory.size() << "/" << SETTINGS.MAX_INVENTORY_SIZE << ")");
        return false;
    }
    
    auto& itemPtr = equippedItems[slotIndex];
    inventory.push_back(std::move(itemPtr));
    equippedItems[slotIndex] = nullptr;
    
    return true;
}

void InventorySystem::UseEquippedItem(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= SETTINGS.EQUIPMENT_SLOTS || IsSlotEmpty(slotIndex)) {
        return;
    }
    
    auto& item = equippedItems[slotIndex];
    auto* player = EngineCore::GameWorld::Instance()->FindPlayer();
    if (!player) {
        LOG_ERROR("Player not found!");
        return;
    }
    
    // Apply item effects based on type
    switch (item->GetType()) {
        case ItemType::HEALTH_POTION: {
            auto healthComponent = player->GetComponent<HealthComponent>();
            if (healthComponent) {
                healthComponent->AddHealth(50);
            } 
            break;
        }
        case ItemType::ARMOR: {
            auto armorComponent = player->GetComponent<ArmorComponent>();
            if (armorComponent) {
                armorComponent->AddArmor(25);
            }
            break;
        }
        case ItemType::AMMO: {
            auto ammoComponent = player->GetComponent<AmmoComponent>();
            if (ammoComponent) {
                ammoComponent->AddAmmo(15);
            }
            break;
        }
        default:
            break;
    }
    
    item->AddCount(-1);
    if (item->GetCount() <= 0) {
        equippedItems[slotIndex].reset();
    }
}

const Item* InventorySystem::GetEquippedItem(int slotIndex) const {
    if (slotIndex < 0 || slotIndex >= SETTINGS.EQUIPMENT_SLOTS || IsSlotEmpty(slotIndex)) {
        return nullptr;
    }
    return equippedItems[slotIndex].get();
}

bool InventorySystem::IsSlotEmpty(int slotIndex) const {
    if (slotIndex < 0 || slotIndex >= SETTINGS.EQUIPMENT_SLOTS) {
        return true;
    }
    return equippedItems[slotIndex] == nullptr;
}

bool InventorySystem::SwapInventoryItems(int index1, int index2) {
    if (index1 < 0 || index1 >= inventory.size() ||
        index2 < 0 || index2 >= inventory.size() ||
        index1 == index2) {
        LOG_ERROR("Invalid inventory indices for swap: " << index1 << ", " << index2 << " (inventory size: " << inventory.size() << ")");
        return false;
    }
    
    std::swap(inventory[index1], inventory[index2]);
    return true;
}

bool InventorySystem::SwapEquipmentSlots(int slot1, int slot2) {
    if (slot1 < 0 || slot1 >= SETTINGS.EQUIPMENT_SLOTS ||
        slot2 < 0 || slot2 >= SETTINGS.EQUIPMENT_SLOTS ||
        slot1 == slot2) {
        LOG_ERROR("Invalid equipment slots for swap: " << slot1 << ", " << slot2);
        return false;
    }
    
    std::swap(equippedItems[slot1], equippedItems[slot2]);
    return true;
}

bool InventorySystem::SwapInventoryToEquipment(int inventoryIndex, int equipmentSlot) {
    if (inventoryIndex < 0 || inventoryIndex >= inventory.size() ||
        equipmentSlot < 0 || equipmentSlot >= SETTINGS.EQUIPMENT_SLOTS) {
        LOG_ERROR("Invalid indices for swap: inventory " << inventoryIndex << ", equipment " << equipmentSlot);
        return false;
    }
    
    if (!IsSlotEmpty(equipmentSlot)) {
        if (inventory.size() >= SETTINGS.MAX_INVENTORY_SIZE) {
            LOG_ERROR("Cannot swap - inventory is full! (size: " << inventory.size() << "/" << SETTINGS.MAX_INVENTORY_SIZE << ")");
            return false;
        }
        inventory.push_back(std::move(equippedItems[equipmentSlot]));
    }
    
    equippedItems[equipmentSlot] = std::move(inventory[inventoryIndex]);
    inventory[inventoryIndex] = nullptr;
    inventory.erase(std::remove(inventory.begin(), inventory.end(), nullptr), inventory.end());
    
    return true;
}

int InventorySystem::FindFirstEmptyInventorySlot() const {
    if (inventory.size() < SETTINGS.MAX_INVENTORY_SIZE) {
        return static_cast<int>(inventory.size());
    }
    
    LOG_WARN("Inventory is full! No empty slots available.");
    return -1;
}

}