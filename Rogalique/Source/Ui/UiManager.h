#pragma once
#include <SFML/Graphics.hpp>


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
    
    void AddElement(std::shared_ptr<UiElement> element);
    void RemoveElement(std::shared_ptr<UiElement> element);
    void ClearElements();
    
    std::vector<std::shared_ptr<UiElement>> GetAllElements();

   private:
    std::vector<std::shared_ptr<UiElement>> uiElements;
    sf::RenderWindow* window = nullptr;
    
};
};  // namespace Rogalique
