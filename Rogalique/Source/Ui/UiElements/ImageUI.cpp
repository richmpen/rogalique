#include "ImageUI.h"
#include "DragDropManager.h"
#include "RenderSystem.h"
#include "InventorySystem.h"

namespace Rogalique {

ImageUI::ImageUI(const std::string& textureName, sf::IntRect rect,
                               sf::Vector2f position)
    : elementRect(rect), elementPosition(position), elementScale(1.0f, 1.0f), originInCenter(true) {
    SetTextureFromMap(textureName, rect);
    SetPosition(position);
    SetScale(elementScale);
    
    bounds = sprite.getGlobalBounds();
}

ImageUI::ImageUI(const std::string& textureName, sf::Vector2f size, sf::Vector2f position)
    : elementPosition(position), elementScale(size.x, size.y), originInCenter(true) {
    SetTexture(textureName);
    SetPosition(position);
    SetElementScale(elementScale);
    if (originInCenter) {
        SetCenterOrigin();
    }
    
    bounds = sprite.getGlobalBounds();
}

void ImageUI::Update(float deltaTime) {
    bounds = sprite.getGlobalBounds();
}

void ImageUI::Render(sf::RenderWindow& window) {
    if (texture) {
        window.draw(sprite);
    }
}

bool ImageUI::HandleEvent(const sf::Event& event) {
    if (!isActive) return false;
    
    if (inventoryIndex < 0 && equipmentSlot < 0) return false;
    
    auto& window = EngineCore::RenderSystem::Instance()->GetMainWindow();
    auto oldView = window.getView();
    window.setView(window.getDefaultView());
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    window.setView(oldView);
    

    if (isEquipmentSlot) {

        if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left && DragDropManager::GetDraggedItem() && 
                bounds.contains(mousePos)) {
                if (onDropCallback && this != DragDropManager::GetDraggedItem()) {
                    onDropCallback(DragDropManager::GetDraggedItem());
                    return true;
                }
            }
        }
        return false;
    }
    
    if (equipmentSlot >= 0 && inventoryIndex < 0 && !DragDropManager::IsDragging()) {
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Right && bounds.contains(mousePos)) {
                
                DragDropManager::ReturnEquipmentItemToInventory(equipmentSlot);
                return true;
            }
        }
    }
    
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left && bounds.contains(mousePos)) {
            if (!DragDropManager::IsDragging()) {
                DragDropManager::StartDragging(this, mousePos, elementPosition);
                return true;
            }
        }
    }
    
    else if (event.type == sf::Event::MouseMoved && DragDropManager::GetDraggedItem() == this) {
        DragDropManager::UpdateDragPosition(mousePos);
        return true;
    }
    
    else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left && DragDropManager::IsDragging()) {
            
            bool dropped = false;
            if (onDropCallback && bounds.contains(mousePos) && this != DragDropManager::GetDraggedItem()) {
                onDropCallback(DragDropManager::GetDraggedItem());
                dropped = true;
            }
            
            if (DragDropManager::GetDraggedItem() != this && dropped) {
                return true;
            }
            
            if (DragDropManager::GetDraggedItem() == this) {
                DragDropManager::EndDragging(mousePos);
                return true;
            }
        }
    }
    
    return false;
}

void ImageUI::SetElement(sf::IntRect newRect) {
    elementRect = newRect;
    sprite.setTextureRect(newRect);
    bounds = sprite.getGlobalBounds();
}

void ImageUI::SetElementPosition(sf::Vector2f newPosition) {
    elementPosition = newPosition;
    UiElement::SetPosition(newPosition);
    bounds = sprite.getGlobalBounds();
}

void ImageUI::SetElementScale(sf::Vector2f newScale) {
    
    elementScale = newScale;
    SetScale(newScale);
    bounds = sprite.getGlobalBounds();
}

void ImageUI::SetElementColor(sf::Color newColor) {
    elementColor = newColor;
    SetColor(newColor);
}

void ImageUI::SetElementOriginCenter() {
    SetCenterOrigin();
    bounds = sprite.getGlobalBounds();
}




}

