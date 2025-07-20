#pragma once
#include "GameState.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "UiManager.h"
#include <memory>
#include <vector>


namespace Rogalique {

    class InventoryState : public EngineCore::GameState {
    public:
        InventoryState();
        ~InventoryState();
        
        void Update(float deltaTime) override;
        void Render() override;
        void HandleEvent(const sf::Event& event) override;
        
        EngineCore::GameObject* GetGameObject() { return gameObject; }
        
    private:
        // UI management methods
        void CreateInventoryGrid();
        void UpdateEquipmentSlots();
        void ReturnItemToInventory(int equipmentSlot);
        
        // Drag and drop handlers
        void OnItemDraggedToEquipment(ImageUI* draggedItem, int equipmentSlot);
        void OnItemDraggedToInventory(ImageUI* draggedItem);
        void OnItemDraggedToInventoryItem(ImageUI* draggedItem, int targetInventoryIndex);
        
        // Core UI components
        std::shared_ptr<UiManager> uiManager;
        EngineCore::GameObject* gameObject;
        
        // Equipment slots
        std::vector<std::shared_ptr<ImageUI>> equipmentSlots{3};
        std::vector<std::shared_ptr<ImageUI>> equipmentItems{3};
        
        // Inventory elements
        std::vector<std::shared_ptr<ImageUI>> inventoryItems;
        std::vector<std::shared_ptr<ImageUI>> inventorySlots;
        
        // Count text elements
        std::vector<std::shared_ptr<TextUI>> countTexts;
        std::vector<std::shared_ptr<TextUI>> equipmentCountTexts;
    };
}
