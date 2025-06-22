#include "pch.h"

#include "../EntitySystem/Systems/RenderSystem.h"

namespace EngineCore {

RenderSystem* RenderSystem::Instance() {
    static RenderSystem render;
    return &render;
}

void RenderSystem::SetMainWindow(sf::RenderWindow* newWindow) {
    LOG_INFO("Setting MainWindow: " << newWindow);
    window = newWindow;
}

sf::RenderWindow& RenderSystem::GetMainWindow() const { return *window; }

void RenderSystem::Render(const sf::Drawable& drawable) {
    window->draw(drawable);
}
}  // namespace EngineCore