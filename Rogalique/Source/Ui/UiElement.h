#pragma once
#include "GameObject.h"
#include "ResourceSystem.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace Rogalique {
enum class UIEventType { Click, Hover, Leave };
class UiElement {
   public:
    virtual void Update(float deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual ~UiElement() = default;

    virtual bool HandleEvent(const sf::Event& event) { return false; }
    virtual void OnUIEvent(UIEventType type) {}

    void SetActive(bool active) { isActive = active; }
    bool IsActive() const { return isActive; }

    void SetTexture(const std::string textureName);
    void SetTextureFromMap(const std::string& textureName, sf::IntRect rect);
    virtual void SetPosition(sf::Vector2f position);
    virtual void SetScale(sf::Vector2f scale);
    sf::Vector2f GetScale();
    virtual void SetColor(sf::Color color);
    virtual void SetCenterOrigin();

    sf::Vector2f GetPosition() const { return sprite.getPosition(); }
    sf::FloatRect GetBounds() const { return bounds; }

   protected:
    sf::Sprite sprite;
    sf::Font font;
    const sf::Texture* texture = nullptr;

    bool isActive = true;
    sf::FloatRect bounds;
};

}  // namespace Rogalique