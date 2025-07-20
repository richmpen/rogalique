#pragma once
#include "Ui/UiElement.h"
#include <functional>

namespace Rogalique {

class ImageUI : public UiElement {
   public:
    ImageUI(const std::string& textureName, sf::IntRect rect,
                   sf::Vector2f position);
    ImageUI(const std::string& textureName, sf::Vector2f size,
                   sf::Vector2f position);
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    bool HandleEvent(const sf::Event& event) override;
    
    void SetElement(sf::IntRect newRect);
    void SetElementPosition(sf::Vector2f newPosition);
    void SetElementScale(sf::Vector2f newScale);
    void SetElementColor(sf::Color newColor);
    void SetElementOriginCenter();
    
    void SetInventoryIndex(int index) { inventoryIndex = index; }
    void SetEquipmentSlot(int slot) { equipmentSlot = slot; }
    void SetIsEquipmentSlot(bool isSlot) { isEquipmentSlot = isSlot; }
    
    int GetInventoryIndex() const { return inventoryIndex; }
    int GetEquipmentSlot() const { return equipmentSlot; }
    bool IsEquipmentSlot() const { return isEquipmentSlot; }
    
    void SetOnDrop(std::function<void(ImageUI*)> callback) { onDropCallback = callback; }
    
   private:
    bool originInCenter;
    sf::IntRect elementRect;
    sf::Vector2f elementPosition;
    sf::Vector2f elementScale;
    sf::Color elementColor;
    
    int inventoryIndex = -1;
    int equipmentSlot = -1;
    bool isEquipmentSlot = false;
    
    std::function<void(ImageUI*)> onDropCallback;
};

}
