#pragma once
#include "GameSettings.h"
#include "Item.h"
#include "ItemType.h"
#include "SpriteColliderComponent.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <vector>

namespace Rogalique {

class InventorySystem {
   public:
    static InventorySystem* Instance();

    void ItemCollision(std::shared_ptr<Item> item);
    void AddItemToInventory(std::shared_ptr<Item> item);
    void Update(float deltaTime);
    void Render();
    const std::vector<std::shared_ptr<Item>>& GetInventory() const {
        return inventory;
    }

    bool EquipItem(int slotIndex, int inventoryIndex);
    bool UnequipItem(int slotIndex);
    void UseEquippedItem(int slotIndex);
    const Item* GetEquippedItem(int slotIndex) const;
    bool IsSlotEmpty(int slotIndex) const;

    bool SwapInventoryItems(int firstIndex, int secondIndex);
    bool SwapEquipmentSlots(int firstSlot, int secondSlot);
    bool SwapInventoryToEquipment(int inventoryIndex, int equipmentSlot);

    int FindFirstEmptyInventorySlot() const;

   private:
    std::vector<std::shared_ptr<Item>> inventory;
    std::vector<std::shared_ptr<Item>> equippedItems;

    static InventorySystem* instance;
};
}  // namespace Rogalique
