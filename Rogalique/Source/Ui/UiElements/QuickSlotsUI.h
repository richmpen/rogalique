#pragma once
#include "ImageUI.h"
#include "InventorySystem.h"
#include "TextUI.h"
#include "Ui/UiElement.h"

#include <memory>
#include <vector>

namespace Rogalique {

class QuickSlotsUI : public UiElement {
   public:
    QuickSlotsUI();
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;

   private:
    void UpdateSlots();

    struct SlotData {
        std::shared_ptr<ImageUI> image;
        std::shared_ptr<ImageUI> itemSprite;

        std::shared_ptr<TextUI> keyText;
        std::shared_ptr<TextUI> countText;
        bool hasItem = false;
    };

    std::vector<SlotData> slots{3};
    const sf::Texture* backgroundTexture = nullptr;
    sf::Font font;
};

}  // namespace Rogalique