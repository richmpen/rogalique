#include "UiManager.h"

#include "GameObject.h"
#include "RenderSystem.h"

#include <SFML/Graphics.hpp>

namespace Rogalique {

UiManager::UiManager(EngineCore::GameObject* gameObject)
    : EngineCore::Component(gameObject) {
    // Получаем окно из RenderSystem
    window = &EngineCore::RenderSystem::Instance()->GetMainWindow();
}

void UiManager::Update(float deltaTime) {
    // Обновляем все UI элементы
    for (auto& element : uiElements) {
        if (element) {
            element->Update(deltaTime);
        }
    }
}

void UiManager::Render() {
    // Рендерим все UI элементы
    if (window) {
        // Сохраняем текущий view
        auto oldView = window->getView();
        // Ставим дефолтный view (экранные координаты)
        window->setView(window->getDefaultView());
        for (auto& element : uiElements) {
            if (element) {
                element->Render(*window);
            }
        }
        // Возвращаем старый view
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

}  // namespace Rogalique