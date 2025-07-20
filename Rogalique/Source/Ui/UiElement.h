#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "ResourceSystem.h"
// #include "GameSettings.h"
#include <memory>

namespace Rogalique {
enum class UIEventType {
    Click,
    Hover,
    Leave
};
class UiElement {
   public:
    virtual void Update(float deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual ~UiElement() = default;

    virtual bool HandleEvent(const sf::Event& event) { return false; }
    virtual void OnUIEvent(UIEventType type) {}
    
    bool Contains(sf::Vector2f point) const;
        
    void SetActive(bool active) { isActive = active; }
    bool IsActive() const { return isActive; }

   protected:
    void SetTexture(const std::string textureName);
    void SetTextureFromMap(const std::string& textureName, sf::IntRect rect);
    void SetPosition(sf::Vector2f position);
    void SetScale(sf::Vector2f scale);
    void SetColor(sf::Color color);
    void SetCenterOrigin();
    sf::Sprite sprite;
    sf::Font font;
    const sf::Texture* texture = nullptr;

    bool isActive = true;
    sf::FloatRect bounds;
};

}  // namespace Rogalique