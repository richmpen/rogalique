#include "TabsUI.h"

namespace Rogalique {

TabsUI::TabsUI(const sf::Vector2f& position, const sf::Vector2f& size)
    : position(position), size(size), activeTabIndex(-1) {
}

void TabsUI::Update(float deltaTime) {
   
    for (auto& button : tabButtons) {
        if (button) {
            button->Update(deltaTime);
        }
    }
    
    // Update active tab elements
    if (activeTabIndex >= 0 && activeTabIndex < tabs.size()) {
        for (auto& element : tabs[activeTabIndex].elements) {
            if (element) {
                element->Update(deltaTime);
            }
        }
    }
}

void TabsUI::Render(sf::RenderWindow& window) {
   
    for (auto& button : tabButtons) {
        if (button) {
            button->Render(window);
        }
    }
    
    // Render active tab elements
    if (activeTabIndex >= 0 && activeTabIndex < tabs.size()) {
        for (auto& element : tabs[activeTabIndex].elements) {
            if (element) {
                element->Render(window);
            }
        }
    }
}

bool TabsUI::HandleEvent(const sf::Event& event) {
   
    for (auto& button : tabButtons) {
        if (button && button->HandleEvent(event)) {
            return true;
        }
    }
    
    // Handle active tab elements events
    if (activeTabIndex >= 0 && activeTabIndex < tabs.size()) {
        for (auto& element : tabs[activeTabIndex].elements) {
            if (element && element->HandleEvent(event)) {
                return true;
            }
        }
    }
    
    return false;
}

void TabsUI::AddTab(const std::string& tabName) {
    tabs.emplace_back(tabName);
    CreateTabButtons();
    
    if (activeTabIndex == -1) {
        SetActiveTab(0);
    }
}

void TabsUI::SetActiveTab(int tabIndex) {
    if (tabIndex >= 0 && tabIndex < tabs.size()) {
        // Deactivate all tabs
        for (auto& tab : tabs) {
            tab.isActive = false;
        }
        
        // Activate selected tab
        tabs[tabIndex].isActive = true;
        activeTabIndex = tabIndex;
        
        // Update button colors
        for (int i = 0; i < tabButtons.size(); ++i) {
            if (tabButtons[i]) {
                if (i == activeTabIndex) {
                    tabButtons[i]->SetElementColor(sf::Color::Green);
                } else {
                    tabButtons[i]->SetElementColor(sf::Color::Blue);
                }
            }
        }
        
        // Call callback if set
        if (onTabChanged) {
            onTabChanged(tabIndex);
        }
    }
}

void TabsUI::AddElementToTab(int tabIndex, std::shared_ptr<UiElement> element) {
    if (tabIndex >= 0 && tabIndex < tabs.size() && element) {
        tabs[tabIndex].elements.push_back(element);
    }
}

void TabsUI::CreateTabButtons() {
    tabButtons.clear();
    
    for (int i = 0; i < tabs.size(); ++i) {
        float buttonX = position.x + i * (120.f + 5.0f);
        float buttonY = position.y;
        
        auto button = std::make_shared<ButtonUI>(
            tabs[i].name,
            "UiMap2",
            sf::IntRect(1649, 1524, 1216, 182),
            sf::Vector2f(buttonX, buttonY),
            sf::Vector2f(120.f, 40.f),
            sf::Color::Green
        );
        
        button->SetElementOriginCenter();
        
        int tabIndex = i;
        button->SetOnClick([this, tabIndex]() {
            SetActiveTab(tabIndex);
        });
        
        tabButtons.push_back(button);
    }
}

void TabsUI::UpdateTabVisibility() {
    for (int i = 0; i < tabs.size(); ++i) {
        tabs[i].isActive = (i == activeTabIndex);
    }
}

} 