#pragma once
#include "ButtonUI.h"
#include "UiElement.h"

#include <functional>
#include <vector>

namespace Rogalique {

struct TabPanel {
    std::string name;
    std::vector<std::shared_ptr<UiElement>> elements;
    bool isActive;

    TabPanel(const std::string& tabName) : name(tabName), isActive(false) {}
};

class TabsUI : public UiElement {
   public:
    TabsUI(const sf::Vector2f& position, const sf::Vector2f& size);

    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    bool HandleEvent(const sf::Event& event) override;

    void AddTab(const std::string& tabName);
    void SetActiveTab(int tabIndex);
    int GetActiveTab() const { return activeTabIndex; }

    void AddElementToTab(int tabIndex, std::shared_ptr<UiElement> element);

    void SetOnTabChanged(std::function<void(int)> callback) {
        onTabChanged = callback;
    }

   private:
    void CreateTabButtons();
    void UpdateTabVisibility();

    std::vector<TabPanel> tabs;
    std::vector<std::shared_ptr<ButtonUI>> tabButtons;

    std::function<void(int)> onTabChanged;

    sf::Vector2f position;
    sf::Vector2f size;
    int activeTabIndex;
};

}  // namespace Rogalique