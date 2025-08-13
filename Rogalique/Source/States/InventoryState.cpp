#include "InventoryState.h"

#include "ButtonUI.h"
#include "GameSettings.h"
#include "GameStateManager.h"
#include "GameWorld.h"
#include "ImageUI.h"
#include "InventorySystem.h"
#include "Item.h"
#include "RenderSystem.h"
#include "TextUI.h"

namespace Rogalique {

InventoryState::InventoryState() {
    EngineCore::GameWorld::Instance()->SetPaused(true);

    auto uiGameObject =
        EngineCore::GameWorld::Instance()->CreateGameObject("InventoryUI");
    uiManager = std::make_unique<UiManager>(uiGameObject);

    if (!uiManager) {
        LOG_ERROR("Cannot create UI - uiManager is null");
        return;
    }

    CreateUi();
}

InventoryState::~InventoryState() {
    EngineCore::GameWorld::Instance()->SetPaused(false);
}

void InventoryState::Update(float deltaTime) {
    if (uiManager) {
        uiManager->Update(deltaTime);
    }
}

void InventoryState::Render() {
    if (uiManager) {
        uiManager->Render();
    }
}

void InventoryState::HandleEvent(const sf::Event& event) {
    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f mousePos = GetMousePosition();

        // Handle inventory item clicks with proper bounds checking
        for (auto i = 0; i < inventoryItems.size(); ++i) {
            if (inventoryItems[i] &&
                inventoryItems[i]->GetBounds().contains(mousePos)) {
                HandleInventoryItemClick(i);
                return;
            }
        }

        // Handle equipment item clicks with proper bounds checking
        for (auto i = 0; i < equipmentItems.size(); ++i) {
            if (equipmentItems[i] &&
                equipmentItems[i]->GetBounds().contains(mousePos)) {
                HandleEquipmentItemClick(i);
                return;
            }
        }
    }

    // Handle other UI elements after item clicks
    if (uiManager) {
        for (auto& element : uiManager->GetAllElements()) {
            if (element && element->HandleEvent(event)) {
                return;
            }
        }
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape ||
            event.key.code == sf::Keyboard::Tab) {
            EngineCore::GameStateManager::Instance()->PopState();
        }
    }
}

void InventoryState::CreateUi() {
    auto panel = std::make_shared<ImageUI>(
        "inventoryPanelMap", sf::IntRect(0, 0, 1123, 608),
        sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH / 2.0f,
                     SETTINGS.PLAYER_CAMERA_HEIGHT / 2.0f));
    panel->SetScale(sf::Vector2f{1.3f, 1.3f});
    panel->SetCenterOrigin();
    uiManager->AddElement(panel);

    auto playerPanelBackground = std::make_shared<ImageUI>(
        "inventoryPanelMap", sf::IntRect(1460, 0, 461, 474),
        sf::Vector2f(585.0f, 570.0f));
    playerPanelBackground->SetScale(sf::Vector2f{1.3f, 1.3f});
    playerPanelBackground->SetCenterOrigin();
    uiManager->AddElement(playerPanelBackground);

    auto playerVisualization = std::make_shared<ImageUI>(
        "inventoryPanelMap", sf::IntRect(1137, 105, 325, 264),
        sf::Vector2f(555.0f, 580.0f));
    playerVisualization->SetScale(sf::Vector2f{1.3f, 1.3f});
    playerVisualization->SetCenterOrigin();
    uiManager->AddElement(playerVisualization);

    auto playerLightPanel = std::make_shared<ImageUI>(
        "inventoryPanelMap", sf::IntRect(1124, 485, 370, 124),
        sf::Vector2f(530.0f, 785.0f));
    playerLightPanel->SetScale(sf::Vector2f{1.3f, 1.3f});
    playerLightPanel->SetCenterOrigin();
    uiManager->AddElement(playerLightPanel);

    auto closeButton = std::make_shared<ButtonUI>(
        "", "inventoryPanelMap", sf::IntRect(1315, 0, 40, 40),
        sf::Vector2f(1550.0f, 205.0f), sf::Vector2f(40, 40), sf::Color::White);
    closeButton->SetCenterOrigin();
    closeButton->SetOnClick(
        [this]() { EngineCore::GameStateManager::Instance()->PopState(); });
    uiManager->AddElement(closeButton);

    // Create equipment slots
    for (int i = 0; i < 3; ++i) {
        auto equipmentIcon = std::make_shared<ImageUI>(
            "inventoryPanelMap", sf::IntRect(1210, 0, 105, 100),
            sf::Vector2f(800.0f, 510.0f + i * 130.0f));

        equipmentIcon->SetScale(sf::Vector2f{1.f, 1.f});
        equipmentIcon->SetCenterOrigin();

        equipmentSlots[i] = equipmentIcon;
        uiManager->AddElement(equipmentIcon);
    }

    CreateInventoryGrid();

    // UI text elements
    auto titleText =
        std::make_shared<TextUI>(48, sf::Vector2f(480.f, 190.f), true);
    titleText->SetText("INVENTORY", true);
    titleText->SetColor(sf::Color::White);
    uiManager->AddElement(titleText);

    auto playerNameText =
        std::make_shared<TextUI>(32, sf::Vector2f(535.f, 780.f), true);
    playerNameText->SetText(SETTINGS.PLAYER_NAME, true);
    playerNameText->SetColor(sf::Color::White);
    uiManager->AddElement(playerNameText);

    auto equipText =
        std::make_shared<TextUI>(32, sf::Vector2f(800.f, 413.f), false);
    equipText->SetText("Equip", true);
    equipText->SetColor(sf::Color::White);
    uiManager->AddElement(equipText);

    UpdateEquipmentSlots();
}

void InventoryState::CreateInventoryGrid() {
    const float gridIconIndent = 126.0f;

    if (!uiManager) {
        LOG_ERROR("INVENTORY_STATE: uiManager is null in CreateInventoryGrid!");
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
            sf::Vector2f position(1000.0f + j * gridIconIndent,
                                  320.0f + i * gridIconIndent);
            auto gridIcon = std::make_shared<ImageUI>(
                "inventoryPanelMap", sf::IntRect(1123, 0, 85, 85),
                sf::Vector2f(position));
            gridIcon->SetScale(sf::Vector2f{1.3f, 1.3f});
            gridIcon->SetCenterOrigin();

            inventorySlots.push_back(gridIcon);
            uiManager->AddElement(gridIcon);
        }
    }

    // Create inventory items
    auto* inventorySystem = InventorySystem::Instance();
    if (!inventorySystem) {
        LOG_ERROR("INVENTORY_STATE: InventorySystem is null!");
        return;
    }

    const auto& inventory = inventorySystem->GetInventory();

    int itemIndex = 0;
    for (auto index = 0; index < inventory.size(); ++index) {
        if (itemIndex >=
            SETTINGS.INVENTORY_GRID_ROWS * SETTINGS.INVENTORY_GRID_COLS)
            break;

        const auto& itemData = inventory[index];

        int i = itemIndex / SETTINGS.INVENTORY_GRID_COLS;
        int j = itemIndex % SETTINGS.INVENTORY_GRID_COLS;

        sf::Vector2f itemPosition(1000.0f + j * gridIconIndent,
                                  320.0f + i * gridIconIndent);

        auto itemIcon = std::make_shared<ImageUI>(
            itemData->GetTextureName(), sf::Vector2f(85, 85), itemPosition);
        itemIcon->SetScale(sf::Vector2f{0.3f, 0.3f});
        itemIcon->SetCenterOrigin();

        inventoryItems.push_back(itemIcon);
        uiManager->AddElement(itemIcon);

        // Display item count if > 1
        if (itemData->GetCount() > 1) {
            auto countText = std::make_shared<TextUI>(
                16, sf::Vector2f(itemPosition.x + 25.f, itemPosition.y + 25.f),
                false);
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
        LOG_ERROR(
            "INVENTORY_STATE: uiManager is null in UpdateEquipmentSlots!");
        return;
    }

    auto* inventorySystem = InventorySystem::Instance();
    if (!inventorySystem) {
        LOG_ERROR("INVENTORY_STATE: InventorySystem is null!");
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
                equippedItem->GetTextureName(), sf::Vector2f(85, 85), position);
            itemIcon->SetScale(sf::Vector2f{0.2f, 0.2f});
            itemIcon->SetCenterOrigin();

            equipmentItems[i] = itemIcon;
            uiManager->AddElement(itemIcon);

            // Display item count if > 1
            if (equippedItem->GetCount() > 1) {
                auto countText = std::make_shared<TextUI>(
                    16, sf::Vector2f(position.x + 25.f, position.y + 25.f),
                    false);
                countText->SetText(std::to_string(equippedItem->GetCount()),
                                   true);
                countText->SetColor(sf::Color::White);
                uiManager->AddElement(countText);
                equipmentCountTexts.push_back(countText);
            }
        }
    }
}

void InventoryState::HandleInventoryItemClick(int inventoryIndex) {
    auto* inventorySystem = InventorySystem::Instance();
    if (!inventorySystem) {
        return;
    }

    // Check if inventory index is valid
    const auto& inventory = inventorySystem->GetInventory();
    if (inventoryIndex < 0 ||
        inventoryIndex >= static_cast<int>(inventory.size())) {
        return;
    }

    // Find first empty equipment slot
    for (int equipSlot = 0; equipSlot < 3; ++equipSlot) {
        const auto* equippedItem = inventorySystem->GetEquippedItem(equipSlot);
        if (equippedItem == nullptr) {
            // Found empty slot - equip item
            if (inventorySystem->EquipItem(equipSlot, inventoryIndex)) {
                UpdateEquipmentSlots();
                CreateInventoryGrid();
            }
            return;
        }
    }
}

void InventoryState::HandleEquipmentItemClick(int equipmentSlot) {
    auto* inventorySystem = InventorySystem::Instance();
    if (!inventorySystem) {
        return;
    }

    // Check if there's actually an item in this slot
    const auto* equippedItem = inventorySystem->GetEquippedItem(equipmentSlot);
    if (equippedItem != nullptr) {
        // Unequip item (add to inventory)
        if (inventorySystem->UnequipItem(equipmentSlot)) {
            UpdateEquipmentSlots();
            CreateInventoryGrid();
        }
    }
}

sf::Vector2f InventoryState::GetMousePosition() {
    auto& window = EngineCore::RenderSystem::Instance()->GetMainWindow();
    auto oldView = window.getView();
    window.setView(window.getDefaultView());
    sf::Vector2f mousePos =
        window.mapPixelToCoords(sf::Mouse::getPosition(window));
    window.setView(oldView);
    return mousePos;
}

}  // namespace Rogalique