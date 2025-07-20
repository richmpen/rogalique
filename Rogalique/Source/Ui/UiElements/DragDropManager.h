#pragma once
#include "ImageUI.h"
#include <SFML/Graphics.hpp>

namespace Rogalique {

class DragDropManager {
public:
    static bool IsDragging() { return draggedItem != nullptr; }
    static ImageUI* GetDraggedItem() { return draggedItem; }
    static void ClearDraggedItem() { draggedItem = nullptr; }
    
    static bool NeedsUIUpdate() { return needsUIUpdate; }
    static void ClearUIUpdateFlag() { needsUIUpdate = false; }
    
    static void ReturnEquipmentItemToInventory(int equipmentSlot);
    
    static void StartDragging(ImageUI* item, const sf::Vector2f& mousePos, const sf::Vector2f& itemPos);
    static void UpdateDragPosition(const sf::Vector2f& mousePos);
    static void EndDragging(const sf::Vector2f& mousePos);
    static void ResetToOriginalPosition();

private:
    static ImageUI* draggedItem;
    static sf::Vector2f dragOffset;
    static sf::Vector2f originalPosition;
    
    static bool needsUIUpdate;
};

} 