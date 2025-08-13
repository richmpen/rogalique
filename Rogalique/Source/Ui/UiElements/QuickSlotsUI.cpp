#include "QuickSlotsUI.h"
#include "GameSettings.h"
#include "ResourceSystem.h"
#include "Item.h"

namespace Rogalique {

QuickSlotsUI::QuickSlotsUI() {

    for (int i = 0; i < 3; ++i) {
        auto& slot = slots[i];
        
        slot.image = std::make_shared<ImageUI>("inventoryPanelMap", sf::IntRect(1210, 0, 105, 100),
                           sf::Vector2f(SETTINGS.SCREEN_WIDTH-350+i* 100.0f, SETTINGS.SCREEN_HEIGHT-200.0f));
        slot.image->SetScale(sf::Vector2f(0.8,0.8));

        slot.keyText = std::make_shared<TextUI>(16, sf::Vector2f(SETTINGS.SCREEN_WIDTH-350+i* 100.0f, SETTINGS.SCREEN_HEIGHT-200.0f), false);
        slot.keyText->SetText(std::to_string(i+1), false);
        
        slot.countText = std::make_shared<TextUI>(14, sf::Vector2f(0,0), false);
        
    }
}

void QuickSlotsUI::Update(float deltaTime) {
    UpdateSlots();
}

void QuickSlotsUI::Render(sf::RenderWindow& window) {
    for (auto& slot : slots) {
        
        if (slot.image) {
            slot.image->Render(window);
        }
        
        if (slot.hasItem) {
            slot.itemSprite->Render(window);
            slot.countText->Render(window);
        }
        
        slot.keyText->Render(window);
    }
}

void QuickSlotsUI::UpdateSlots() {
    auto* inventorySystem = InventorySystem::Instance();
    if (!inventorySystem) return;
    
    for (int i = 0; i < 3; ++i) {
        auto& slot = slots[i];
        const auto* item = inventorySystem->GetEquippedItem(i);
        
        if (item) {
            slot.hasItem = true;

            
            slot.itemSprite = std::make_shared<ImageUI>(
                item->GetTextureName(), 
                sf::Vector2f(1,1),
                sf::Vector2f(SETTINGS.SCREEN_WIDTH-350+i* 100.0f+40, SETTINGS.SCREEN_HEIGHT-200.0f+30));
            
            
            slot.itemSprite->SetScale(sf::Vector2f(0.18f, 0.18f));
            slot.itemSprite->SetCenterOrigin();
            
            if (item->GetCount() > 1) {
                slot.countText->SetText(std::to_string(item->GetCount()),false);
                slot.countText->SetTextPosition(sf::Vector2f(SETTINGS.SCREEN_WIDTH-350+i* 100.0f+70, SETTINGS.SCREEN_HEIGHT-200.0f+60));
            } else {
                slot.countText->SetText("", false);
            }
        } else {
            slot.hasItem = false;
            slot.countText->SetText("",false);
            
            slot.itemSprite.reset();
        }
    }
}

} 