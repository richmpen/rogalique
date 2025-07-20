#pragma once
#include "GameSettings.h"
#include "SpriteColliderComponent.h"
#include "ItemType.h"
#include <memory>
#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

namespace Rogalique {
    // Forward declaration
    class Item;
    
    class InventorySystem{
    public:
        static InventorySystem* Instance();
        
        void ItemCollision(EngineCore::GameObject* itemGameObject, ItemType itemType, int itemCount, const std::string& textureName);
        void AddItemToInventory(ItemType type, int count, const std::string& textureName);
        void Update(float deltaTime);
        void Render();
        const std::vector<std::unique_ptr<Item>>& GetInventory() const { return inventory; }
        
        bool EquipItem(int slotIndex, int inventoryIndex);
        bool UnequipItem(int slotIndex);
        void UseEquippedItem(int slotIndex);
        const Item* GetEquippedItem(int slotIndex) const;
        bool IsSlotEmpty(int slotIndex) const;

        bool SwapInventoryItems(int index1, int index2);
        bool SwapEquipmentSlots(int slot1, int slot2);
        bool SwapInventoryToEquipment(int inventoryIndex, int equipmentSlot);
        
        int FindFirstEmptyInventorySlot() const;
    private:
        std::vector<std::unique_ptr<Item>> inventory;
        std::vector<std::unique_ptr<Item>> equippedItems;
        
        static InventorySystem* instance;
        
    };
}

