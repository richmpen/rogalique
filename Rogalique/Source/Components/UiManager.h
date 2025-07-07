#pragma once

#include "Component.h"
#include "UiElement.h"

#include <memory>
#include <vector>

namespace Rogalique {

class UiManager : public EngineCore::Component {
   public:
    UiManager(EngineCore::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

    // Методы для управления UI элементами
    void AddElement(std::shared_ptr<UiElement> element);
    void RemoveElement(std::shared_ptr<UiElement> element);
    void ClearElements();

   private:
    std::vector<std::shared_ptr<UiElement>> uiElements;
    sf::RenderWindow* window = nullptr;
};
};  // namespace Rogalique
