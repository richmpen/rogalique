#include "DragDropManager.h"
#include "InventorySystem.h"
#include "RenderSystem.h"

namespace Rogalique {


ImageUI* DragDropManager::draggedItem = nullptr;
sf::Vector2f DragDropManager::dragOffset = sf::Vector2f(0, 0);
sf::Vector2f DragDropManager::originalPosition = sf::Vector2f(0, 0);
bool DragDropManager::needsUIUpdate = false;

void DragDropManager::StartDragging(ImageUI* item, const sf::Vector2f& mousePos, const sf::Vector2f& itemPos) {
    if (!draggedItem) {
        draggedItem = item;
        originalPosition = itemPos;
        dragOffset = mousePos - itemPos;
        LOG_INFO("Started dragging item from index: " << item->GetInventoryIndex() << " equipment slot: " << item->GetEquipmentSlot());
    }
}

void DragDropManager::UpdateDragPosition(const sf::Vector2f& mousePos) {
    if (draggedItem) {
        sf::Vector2f newPosition = mousePos - dragOffset;
        draggedItem->SetElementPosition(newPosition);
    }
}

void DragDropManager::EndDragging(const sf::Vector2f& mousePos) {
    if (!draggedItem) return;
    
    bool dropped = false;
    
    if (!dropped) {
        
        ResetToOriginalPosition();
    }
    
   
    draggedItem = nullptr;
}

void DragDropManager::ResetToOriginalPosition() {
    if (draggedItem) {
        draggedItem->SetElementPosition(originalPosition);
    }
}

void DragDropManager::ReturnEquipmentItemToInventory(int equipmentSlot) {
    auto* inventorySystem = InventorySystem::Instance();
    if (!inventorySystem) {
        LOG_ERROR("ReturnEquipmentItemToInventory: inventorySystem is null");
        return;
    }
    
    LOG_INFO("Returning item from equipment slot " << equipmentSlot << " to inventory (right click)");
    
    
    if (inventorySystem->IsSlotEmpty(equipmentSlot)) {
        LOG_ERROR("Cannot return item from empty slot " << equipmentSlot);
        return;
    }
    
    bool success = inventorySystem->UnequipItem(equipmentSlot);
    
    if (success) {
        LOG_INFO("Successfully returned item from slot " << equipmentSlot << " to inventory");
        
        needsUIUpdate = true;
    } else {
        LOG_ERROR("Failed to return item from slot " << equipmentSlot);
    }
}

} 