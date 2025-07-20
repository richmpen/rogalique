#include "InventoryState.h"

#include "GameSettings.h"
#include "GameWorld.h"
#include "GameStateManager.h"
#include "InventorySystem.h"
#include "DragDropManager.h"
#include "ImageUI.h"
#include "ButtonUI.h"
#include "TextUI.h"
#include "Item.h"

namespace Rogalique {

    InventoryState::InventoryState() {
        EngineCore::GameWorld::Instance()->SetPaused(true);
        
        auto uiGameObject = EngineCore::GameWorld::Instance()->CreateGameObject("InventoryUI");
        uiManager = std::make_unique<UiManager>(uiGameObject);

        if (!uiManager) {
            LOG_ERROR("Cannot create UI - uiManager is null");
            return;
        }
        
        auto panel = std::make_shared<ImageUI>(
            "inventoryPanelMap", sf::IntRect(0, 0, 1123, 608),
            sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH/2.0f, SETTINGS.PLAYER_CAMERA_HEIGHT/2.0f));
        panel->SetElementScale(sf::Vector2f{1.3f, 1.3f});
        panel->SetElementOriginCenter();
        uiManager->AddElement(panel);

        auto playerPanelBackground = std::make_shared<ImageUI>(
            "inventoryPanelMap", sf::IntRect(1460, 0, 461, 474),
            sf::Vector2f(585.0f, 570.0f));
        playerPanelBackground->SetElementScale(sf::Vector2f{1.3f, 1.3f});
        playerPanelBackground->SetElementOriginCenter();
        uiManager->AddElement(playerPanelBackground);
        
        auto playerVisualization = std::make_shared<ImageUI>(
            "inventoryPanelMap", sf::IntRect(1137, 105, 325, 264),
            sf::Vector2f(555.0f, 580.0f));
        playerVisualization->SetElementScale(sf::Vector2f{1.3f, 1.3f});
        playerVisualization->SetElementOriginCenter();
        uiManager->AddElement(playerVisualization);
        
        auto playerLightPanel = std::make_shared<ImageUI>(
            "inventoryPanelMap", sf::IntRect(1124, 485, 370, 124),
            sf::Vector2f(530.0f, 785.0f));
        playerLightPanel->SetElementScale(sf::Vector2f{1.3f, 1.3f});
        playerLightPanel->SetElementOriginCenter();
        uiManager->AddElement(playerLightPanel);

        auto closeButton = std::make_shared<ButtonUI>(
            "", "inventoryPanelMap", sf::IntRect(1315, 0, 40, 40),
            sf::Vector2f(1550.0f, 205.0f), sf::Vector2f(40, 40),
            sf::Color::White);
        closeButton->SetElementScale(sf::Vector2f{1.3f, 1.3f});
        closeButton->SetElementOriginCenter();
        closeButton->SetOnClick([this]() {
            EngineCore::GameStateManager::Instance()->PopState();
        });
        uiManager->AddElement(closeButton);

        // Create equipment slots
        for (int i = 0; i < 3; ++i) {
            auto equipmentIcon = std::make_shared<ImageUI>(
            "inventoryPanelMap", sf::IntRect(1210, 0, 105, 100),
            sf::Vector2f(800.0f, 510.0f+i*130.0f));

            equipmentIcon->SetElementScale(sf::Vector2f{1.f, 1.f});
            equipmentIcon->SetElementOriginCenter();
            equipmentIcon->SetEquipmentSlot(i);
            equipmentIcon->SetIsEquipmentSlot(true);
            equipmentIcon->SetOnDrop([this, i](ImageUI* draggedItem) {
                OnItemDraggedToEquipment(draggedItem, i);
            });
            
            equipmentSlots[i] = equipmentIcon;
            uiManager->AddElement(equipmentIcon);
        }
        
        CreateInventoryGrid();

        // UI text elements
        auto titleText = std::make_shared<TextUI>(48, sf::Vector2f(480.f, 190.f), true);
        titleText->SetText("INVENTORY", true);
        titleText->SetColor(sf::Color::White);
        uiManager->AddElement(titleText);

        auto playerNameText = std::make_shared<TextUI>(32, sf::Vector2f(535.f, 780.f), true);
        playerNameText->SetText(SETTINGS.PLAYER_NAME, true);
        playerNameText->SetColor(sf::Color::White);
        uiManager->AddElement(playerNameText);

        auto equipText = std::make_shared<TextUI>(32, sf::Vector2f(800.f, 413.f), false);
        equipText->SetText("Equip", true);
        equipText->SetColor(sf::Color::White);
        uiManager->AddElement(equipText);
        
        UpdateEquipmentSlots();
    }

    InventoryState::~InventoryState() {
        EngineCore::GameWorld::Instance()->SetPaused(false);
    }

    void InventoryState::Update(float deltaTime) {
        if (uiManager) {
            uiManager->Update(deltaTime);
        }
        
        if (DragDropManager::NeedsUIUpdate()) {
            UpdateEquipmentSlots();
            CreateInventoryGrid();
            DragDropManager::ClearUIUpdateFlag();
        }
    }

    void InventoryState::Render() {
        if (uiManager) {
            uiManager->Render();
        }
    }

    void InventoryState::HandleEvent(const sf::Event& event) {
        if (uiManager) {
            for (auto& element : uiManager->GetAllElements()) {
                if (element && element->HandleEvent(event)) {
                    return; 
                }
            }
        }
        
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::I) {
                EngineCore::GameStateManager::Instance()->PopState();
            }
        }
    }

    void InventoryState::CreateInventoryGrid() {
        const float gridIconIndent = 126.0f;
        
        if (!uiManager) {
            LOG_ERROR("uiManager is null in CreateInventoryGrid!");
            return;
        }
        
        // Clear existing UI elements
        for (auto& item : inventoryItems) {
            if (item) {
                uiManager->RemoveElement(item);
            }
        }
        inventoryItems.clear();
        
        for (auto& slot : inventorySlots) {
            if (slot) {
                uiManager->RemoveElement(slot);
            }
        }
        inventorySlots.clear();
        
        for (auto& text : countTexts) {
            if (text) {
                uiManager->RemoveElement(text);
            }
        }
        countTexts.clear();
        
        // Create inventory grid slots
        for (int i = 0; i < SETTINGS.INVENTORY_GRID_ROWS; ++i) {
            for (int j = 0; j < SETTINGS.INVENTORY_GRID_COLS; ++j) {
                sf::Vector2f position(1000.0f + j * gridIconIndent, 320.0f + i * gridIconIndent);
                auto gridIcon = std::make_shared<ImageUI>(
                    "inventoryPanelMap",
                    sf::IntRect(1123, 0, 85, 85),
                    sf::Vector2f(position));
                gridIcon->SetElementScale(sf::Vector2f{1.3f, 1.3f});
                gridIcon->SetElementOriginCenter();
                gridIcon->SetOnDrop([this](ImageUI* draggedItem) {
                    OnItemDraggedToInventory(draggedItem);
                });
                
                inventorySlots.push_back(gridIcon);
                uiManager->AddElement(gridIcon);
            }
        }
        
        // Create inventory items
        auto* inventorySystem = InventorySystem::Instance();
        if (!inventorySystem) {
            LOG_ERROR("InventorySystem is null!");
            return;
        }
        
        const auto& inventory = inventorySystem->GetInventory();
        
        int itemIndex = 0;
        for (size_t idx = 0; idx < inventory.size(); ++idx) {
            if (itemIndex >= SETTINGS.INVENTORY_GRID_ROWS * SETTINGS.INVENTORY_GRID_COLS) break;
            
            const auto& itemData = inventory[idx];
            
            int i = itemIndex / SETTINGS.INVENTORY_GRID_COLS;
            int j = itemIndex % SETTINGS.INVENTORY_GRID_COLS;
            
            sf::Vector2f itemPosition(1000.0f + j * gridIconIndent, 320.0f + i * gridIconIndent);
            
            auto itemIcon = std::make_shared<ImageUI>(
                itemData->GetTextureName(),
                sf::Vector2f(85, 85),
                itemPosition);
            itemIcon->SetElementScale(sf::Vector2f{0.3f, 0.3f});
            itemIcon->SetElementOriginCenter();
            itemIcon->SetInventoryIndex(static_cast<int>(idx));
            itemIcon->SetOnDrop([this, idx](ImageUI* draggedItem) {
                OnItemDraggedToInventoryItem(draggedItem, static_cast<int>(idx));
            });
            
            inventoryItems.push_back(itemIcon);
            uiManager->AddElement(itemIcon);
            
            // Display item count if > 1
            if (itemData->GetCount() > 1) {
                auto countText = std::make_shared<TextUI>(
                    16, 
                    sf::Vector2f(itemPosition.x + 25.f, itemPosition.y + 25.f), false
                );
                countText->SetText(std::to_string(itemData->GetCount()), true);
                countText->SetColor(sf::Color::White);
                uiManager->AddElement(countText);
                countTexts.push_back(countText);
            }
            
            itemIndex++;
        }
    }

    void InventoryState::UpdateEquipmentSlots() {
        if (!uiManager) {
            LOG_ERROR("uiManager is null in UpdateEquipmentSlots!");
            return;
        }
        
        auto* inventorySystem = InventorySystem::Instance();
        if (!inventorySystem) {
            LOG_ERROR("InventorySystem is null!");
            return;
        }
        
        // Remove old equipment items
        for (int i = 0; i < 3; ++i) {
            if (equipmentItems[i]) {
                uiManager->RemoveElement(equipmentItems[i]);
                equipmentItems[i] = nullptr;
            }
        }
        
        // Clear equipment count texts
        for (auto& text : equipmentCountTexts) {
            if (text) {
                uiManager->RemoveElement(text);
            }
        }
        equipmentCountTexts.clear();
        
        // Create equipped items
        for (int i = 0; i < 3; ++i) {
            const auto* equippedItem = inventorySystem->GetEquippedItem(i);
            if (equippedItem) {
                sf::Vector2f position(800.0f, 510.0f + i * 130.0f);
                
                auto itemIcon = std::make_shared<ImageUI>(
                    equippedItem->GetTextureName(),
                    sf::Vector2f(85, 85),
                    position);
                itemIcon->SetElementScale(sf::Vector2f{0.4f, 0.4f});
                itemIcon->SetElementOriginCenter();
                itemIcon->SetEquipmentSlot(i);
                itemIcon->SetIsEquipmentSlot(false);
                itemIcon->SetOnDrop([this, i](ImageUI* draggedItem) {
                    OnItemDraggedToEquipment(draggedItem, i);
                });
                
                equipmentItems[i] = itemIcon;
                uiManager->AddElement(itemIcon);
                
                // Display item count if > 1
                if (equippedItem->GetCount() > 1) {
                    auto countText = std::make_shared<TextUI>(
                        16, 
                        sf::Vector2f(position.x + 25.f, position.y + 25.f), false
                    );
                    countText->SetText(std::to_string(equippedItem->GetCount()), true);
                    countText->SetColor(sf::Color::White);
                    uiManager->AddElement(countText);
                    equipmentCountTexts.push_back(countText);
                }
            }
        }
    }
    
    void InventoryState::ReturnItemToInventory(int equipmentSlot) {
        auto* inventorySystem = InventorySystem::Instance();
        if (!inventorySystem) {
            LOG_ERROR("ReturnItemToInventory: inventorySystem is null");
            return;
        }
        
        if (inventorySystem->IsSlotEmpty(equipmentSlot)) {
            LOG_ERROR("Cannot return item from empty slot " << equipmentSlot);
            return;
        }
        
        bool success = inventorySystem->UnequipItem(equipmentSlot);
        
        if (success) {
            UpdateEquipmentSlots();
            CreateInventoryGrid();
        } else {
            LOG_ERROR("Failed to return item from slot " << equipmentSlot);
        }
    }
    
    void InventoryState::OnItemDraggedToEquipment(ImageUI* draggedItem, int equipmentSlot) {
        if (!draggedItem) {
            LOG_ERROR("OnItemDraggedToEquipment: draggedItem is null");
            return;
        }
        
        auto* inventorySystem = InventorySystem::Instance();
        if (!inventorySystem) {
            LOG_ERROR("OnItemDraggedToEquipment: inventorySystem is null");
            return;
        }
        
        int inventoryIndex = draggedItem->GetInventoryIndex();
        int draggedEquipmentSlot = draggedItem->GetEquipmentSlot();
        
        bool success = false;
        
        if (inventoryIndex >= 0) {
            const auto& inventory = inventorySystem->GetInventory();
            if (inventoryIndex >= static_cast<int>(inventory.size())) {
                LOG_ERROR("Invalid inventory index: " << inventoryIndex << " (inventory size: " << inventory.size() << ")");
                return;
            }
            
            if (!inventorySystem->IsSlotEmpty(equipmentSlot)) {
                success = inventorySystem->SwapInventoryToEquipment(inventoryIndex, equipmentSlot);
            } else {
                success = inventorySystem->EquipItem(equipmentSlot, inventoryIndex);
            }
        } 
        else if (draggedEquipmentSlot >= 0) {
            if (draggedEquipmentSlot == equipmentSlot) {
                return;
            }
            success = inventorySystem->SwapEquipmentSlots(draggedEquipmentSlot, equipmentSlot);
        }
        else {
            LOG_ERROR("Invalid item - no valid inventory index or equipment slot");
            return;
        }
        
        if (success) {
            DragDropManager::ClearDraggedItem();
            
            if (inventoryIndex >= 0) {
                CreateInventoryGrid();
            }
            UpdateEquipmentSlots();
        } else {
            LOG_ERROR("Failed to process equipment operation");
        }
    }
    
    void InventoryState::OnItemDraggedToInventory(ImageUI* draggedItem) {
        if (!draggedItem) {
            LOG_ERROR("OnItemDraggedToInventory: draggedItem is null");
            return;
        }
        
        auto* inventorySystem = InventorySystem::Instance();
        if (!inventorySystem) {
            LOG_ERROR("OnItemDraggedToInventory: inventorySystem is null");
            return;
        }
        
        int inventoryIndex = draggedItem->GetInventoryIndex();
        int equipmentSlot = draggedItem->GetEquipmentSlot();
        
        bool success = false;
        
        if (equipmentSlot >= 0 && inventoryIndex < 0) {
            if (inventorySystem->IsSlotEmpty(equipmentSlot)) {
                LOG_ERROR("Cannot unequip from empty slot " << equipmentSlot);
                return;
            }
            
            success = inventorySystem->UnequipItem(equipmentSlot);
        } 
        else if (inventoryIndex >= 0) {
            return;
        }
        else {
            LOG_ERROR("Invalid item - no valid inventory index or equipment slot");
            return;
        }
        
        if (success) {
            DragDropManager::ClearDraggedItem();
            
            if (equipmentSlot >= 0) {
                UpdateEquipmentSlots();
            }
            CreateInventoryGrid();
        } else {
            LOG_ERROR("Failed to process inventory operation");
        }
    }

    void InventoryState::OnItemDraggedToInventoryItem(ImageUI* draggedItem, int targetInventoryIndex) {
        if (!draggedItem) {
            LOG_ERROR("OnItemDraggedToInventoryItem: draggedItem is null");
            return;
        }
        
        auto* inventorySystem = InventorySystem::Instance();
        if (!inventorySystem) {
            LOG_ERROR("OnItemDraggedToInventoryItem: inventorySystem is null");
            return;
        }
        
        int draggedInventoryIndex = draggedItem->GetInventoryIndex();
        int equipmentSlot = draggedItem->GetEquipmentSlot();
        
        if (draggedInventoryIndex < 0 && equipmentSlot < 0) {
            LOG_ERROR("OnItemDraggedToInventoryItem: No valid indices - draggedInventoryIndex: " << draggedInventoryIndex << ", equipmentSlot: " << equipmentSlot);
            return;
        }
        
        bool success = false;
        
        if (draggedInventoryIndex >= 0 && equipmentSlot < 0) {
            if (draggedInventoryIndex != targetInventoryIndex) {
                success = inventorySystem->SwapInventoryItems(draggedInventoryIndex, targetInventoryIndex);
            } else {
                return;
            }
        }
        else if (equipmentSlot >= 0 && draggedInventoryIndex < 0) {
            const auto& inventory = inventorySystem->GetInventory();
            if (targetInventoryIndex >= static_cast<int>(inventory.size())) {
                LOG_ERROR("Invalid target inventory index: " << targetInventoryIndex << " (inventory size: " << inventory.size() << ")");
                return;
            }
            
            if (inventorySystem->IsSlotEmpty(equipmentSlot)) {
                LOG_ERROR("Cannot swap - equipment slot " << equipmentSlot << " is empty");
                return;
            }
            
            success = inventorySystem->SwapInventoryToEquipment(targetInventoryIndex, equipmentSlot);
        }
        else {
            LOG_ERROR("Invalid drag operation - draggedInventoryIndex: " << draggedInventoryIndex << ", equipmentSlot: " << equipmentSlot);
            return;
        }
        
        if (success) {
            DragDropManager::ClearDraggedItem();
            
            if (equipmentSlot >= 0) {
                UpdateEquipmentSlots();
            }
            CreateInventoryGrid();
        } else {
            LOG_ERROR("Failed to process inventory item swap");
        }
    }

}