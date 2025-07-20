
#include "UiManager.h"

#include "GameObject.h"
#include "RenderSystem.h"


namespace Rogalique {

UiManager::UiManager(EngineCore::GameObject* gameObject)
    : EngineCore::Component(gameObject) {
    window = &EngineCore::RenderSystem::Instance()->GetMainWindow();
   
}

void UiManager::Update(float deltaTime) {
    for (auto& element : uiElements) {
        if (element) {
            element->Update(deltaTime);
        }
    }
}

void UiManager::Render() {
    if (window) {
        auto oldView = window->getView();
        window->setView(window->getDefaultView());
        for (auto& element : uiElements) {
            if (element) {
                element->Render(*window);
            }
        }
        window->setView(oldView);
    }
}

void UiManager::AddElement(std::shared_ptr<UiElement> element) {
    if (element) {
        uiElements.push_back(element);
    }
}

void UiManager::RemoveElement(std::shared_ptr<UiElement> element) {
    uiElements.erase(std::remove(uiElements.begin(), uiElements.end(), element),
                     uiElements.end());
}

void UiManager::ClearElements() { uiElements.clear(); }



std::vector<std::shared_ptr<UiElement>> UiManager::GetAllElements() {
    return uiElements;
}
}  // namespace Rogalique