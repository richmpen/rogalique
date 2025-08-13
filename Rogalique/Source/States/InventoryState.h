#pragma once
#include "GameState.h"
#include "ImageUI.h"
#include "TextUI.h"
#include "UiManager.h"

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

namespace Rogalique {

class InventoryState : public EngineCore::GameState {
   public:
    InventoryState();
    ~InventoryState() override;

    void Update(float deltaTime) override;
    void Render() override;
    void HandleEvent(const sf::Event& event) override;

    EngineCore::GameObject* GetGameObject() { return gameObject; }

   private:
    void CreateUi();

    void CreateInventoryGrid();
    void UpdateEquipmentSlots();

    void HandleInventoryItemClick(int inventoryIndex);
    void HandleEquipmentItemClick(int equipmentSlot);
    sf::Vector2f GetMousePosition();

    std::shared_ptr<UiManager> uiManager;
    EngineCore::GameObject* gameObject;

    std::vector<std::shared_ptr<ImageUI>> equipmentSlots{3};
    std::vector<std::shared_ptr<ImageUI>> equipmentItems{3};

    std::vector<std::shared_ptr<ImageUI>> inventoryItems;
    std::vector<std::shared_ptr<ImageUI>> inventorySlots;

    std::vector<std::shared_ptr<TextUI>> countTexts;
    std::vector<std::shared_ptr<TextUI>> equipmentCountTexts;
};
}  // namespace Rogalique
