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

void InventorySystem::ItemCollision(std::shared_ptr<Item> item) {
    auto collider = item->GetGameObject()->GetComponent<EngineCore::SpriteColliderComponent>();
    if (!collider) {
        LOG_ERROR("No collider component found!")
        return;
    }

    std::weak_ptr<Item> weakItem = item;
    
    collider->SubscribeCollision([weakItem, collider](EngineCore::Collision collision) {
        auto item = weakItem.lock();
        if (!item) return;
         
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
            InventorySystem::Instance()->AddItemToInventory(item);
            item->HideInWorld();
        }
    });
}

void InventorySystem::AddItemToInventory(std::shared_ptr<Item> item) {
    if (inventory.size() >= SETTINGS.MAX_INVENTORY_SIZE) {
        LOG_ERROR("INVENTORY: Inventory full! Cannot add item: " << item->GetTextureName());
        return;
    }
    
    inventory.push_back(item);
}

void InventorySystem::Update(float deltaTime) {}

void InventorySystem::Render() {}

bool InventorySystem::EquipItem(int slotIndex, int inventoryIndex) {
    if (slotIndex < 0 || slotIndex >= SETTINGS.EQUIPMENT_SLOTS) {
        LOG_ERROR("INVENTORY: Invalid equipment slot index: " << slotIndex);
        return false;
    }
    
    if (inventoryIndex < 0 || inventoryIndex >= inventory.size()) {
        LOG_ERROR("INVENTORY: Invalid inventory index: " << inventoryIndex);
        return false;
    }
    
    if (!IsSlotEmpty(slotIndex)) {
        UnequipItem(slotIndex);
    }
    
    equippedItems[slotIndex] = inventory[inventoryIndex];
    inventory.erase(inventory.begin() + inventoryIndex);
    
    return true;
}

bool InventorySystem::UnequipItem(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= SETTINGS.EQUIPMENT_SLOTS || IsSlotEmpty(slotIndex)) {
        LOG_ERROR("INVENTORY: Cannot unequip from slot " << slotIndex << " - invalid slot or empty");
        return false;
    }
    
    if (inventory.size() >= SETTINGS.MAX_INVENTORY_SIZE) {
        LOG_ERROR("INVENTORY: Cannot unequip item - inventory is full! (size: " << inventory.size() << "/" << SETTINGS.MAX_INVENTORY_SIZE << ")");
        return false;
    }
    
    inventory.push_back(equippedItems[slotIndex]);
    equippedItems[slotIndex] = nullptr;
    
    return true;
}

void InventorySystem::UseEquippedItem(int slotIndex) {
    if (slotIndex < 0 || slotIndex >= SETTINGS.EQUIPMENT_SLOTS || IsSlotEmpty(slotIndex)) {
        return;
    }
    
    auto& item = equippedItems[slotIndex];
    auto* player = EngineCore::GameWorld::Instance()->FindPlayer();
    
    if (item->Use(player)) {
        item->AddCount(-1);
        if (item->GetCount() <= 0) {
            equippedItems[slotIndex] = nullptr;
        }
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

bool InventorySystem::SwapInventoryItems(int firstIndex, int secondIndex) {
    if (firstIndex < 0 || firstIndex >= inventory.size() ||
        secondIndex < 0 || secondIndex >= inventory.size() ||
        firstIndex == secondIndex) {
        LOG_ERROR("INVENTORY: Invalid inventory indices for swap: " << firstIndex << ", " << secondIndex << " (inventory size: " << inventory.size() << ")");
        return false;
    }
    
    std::swap(inventory[firstIndex], inventory[secondIndex]);
    return true;
}

bool InventorySystem::SwapEquipmentSlots(int firstSlot, int secondSlot) {
    if (firstSlot < 0 || firstSlot >= SETTINGS.EQUIPMENT_SLOTS ||
        secondSlot < 0 || secondSlot >= SETTINGS.EQUIPMENT_SLOTS ||
        firstSlot == secondSlot) {
        LOG_ERROR("INVENTORY: Invalid equipment slots for swap: " << firstSlot << ", " << secondSlot);
        return false;
    }
    
    std::swap(equippedItems[firstSlot], equippedItems[secondSlot]);
    return true;
}

bool InventorySystem::SwapInventoryToEquipment(int inventoryIndex, int equipmentSlot) {
    if (inventoryIndex < 0 || inventoryIndex >= inventory.size() ||
        equipmentSlot < 0 || equipmentSlot >= SETTINGS.EQUIPMENT_SLOTS) {
        LOG_ERROR("INVENTORY: Invalid indices for swap: inventory " << inventoryIndex << ", equipment " << equipmentSlot);
        return false;
    }
    
    if (!IsSlotEmpty(equipmentSlot)) {
        if (inventory.size() >= SETTINGS.MAX_INVENTORY_SIZE) {
            LOG_ERROR("INVENTORY: Cannot swap - inventory is full! (size: " << inventory.size() << "/" << SETTINGS.MAX_INVENTORY_SIZE << ")");
            return false;
        }
        inventory.push_back(equippedItems[equipmentSlot]);
    }
    
    equippedItems[equipmentSlot] = inventory[inventoryIndex];
    inventory.erase(inventory.begin() + inventoryIndex);
    
    return true;
}

int InventorySystem::FindFirstEmptyInventorySlot() const {
    if (inventory.size() < SETTINGS.MAX_INVENTORY_SIZE) {
        return static_cast<int>(inventory.size());
    }
    
    LOG_WARN("INVENTORY: Inventory is full! No empty slots available.");
    return -1;
}

}