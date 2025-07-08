#pragma once
#include "Player.h"
#include "ResourceSystem.h"

#include <SFML/Graphics.hpp>
#include <memory>

namespace Rogalique {

class UiElement {
   public:
    virtual void Update(float deltaTime) = 0;
    virtual void Render(sf::RenderWindow& window) = 0;
    virtual ~UiElement() = default;

   protected:
    void SetTextureFromMap(const std::string& textureName, sf::IntRect rect);
    void SetPosition(sf::Vector2f position);
    void SetScale(sf::Vector2f scale);
    void SetColor(sf::Color color);
    sf::Sprite sprite;
    sf::Font font;
    const sf::Texture* texture = nullptr;
};

class UiTextElement : public UiElement {
public:
    UiTextElement(int size, sf::Vector2f position);

    void Update(float deltaTime) override {}
    void Render(sf::RenderWindow& window) override;

    void SetText(const std::string& newText);
    void SetPosition(sf::Vector2f newPosition);
    void SetColor(sf::Color newColor);
    void SetSize( int newSize);
    void SetStyle(sf::Text::Style style);
private:
    sf::Text text;
};

class HealthBar : public UiElement {
   public:
    HealthBar(const std::string& textureName, sf::IntRect bgRect,
              sf::IntRect barRect, sf::Vector2f position, sf::Vector2f barScale,
              EngineCore::GameObject* player);
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void SetBarPosition(sf::Vector2f newPosition);
    void SetBarScale(sf::Vector2f newScale);
    void SetBarColor(sf::Color newColor);

   private:
    void SetHealth(float current, float max);
    sf::Sprite background;
    sf::Sprite bar;
    float currentHealth = 0;
    float maxHealth = 0;
    sf::IntRect barRectOriginal;
    EngineCore::GameObject* playerGameObject = nullptr;
    sf::Vector2f healthBarPosition;
    sf::Vector2f healthBarScale;
    sf::Color healthBarColor;
};

class ArmorBar : public UiElement {
   public:
    ArmorBar(const std::string& textureName, sf::IntRect bgRect,
             sf::IntRect barRect, sf::Vector2f position, sf::Vector2f barScale,
             EngineCore::GameObject* player);
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void SetBarPosition(sf::Vector2f newPosition);
    void SetBarScale(sf::Vector2f newScale);
    void SetBarColor(sf::Color newColor);

   private:
    void SetArmor(float current, float max);
    sf::Sprite background;
    sf::Sprite bar;
    float currentArmor = 0;
    float maxArmor = 0;
    sf::IntRect barRectOriginal;
    EngineCore::GameObject* playerGameObject = nullptr;
    sf::Vector2f armorBarPosition;
    sf::Vector2f armorBarScale;
    sf::Color armorBarColor;
};

class AmmoBar : public UiElement {
   public:
    AmmoBar(const std::string& textureName, sf::IntRect bgRect,
                 sf::IntRect barRect, std::shared_ptr<UiTextElement> firstText,
                 std::shared_ptr<UiTextElement> secondText, sf::Vector2f position,
                 sf::Vector2f barScale, EngineCore::GameObject* player);
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void SetBarPosition(sf::Vector2f newPosition);
    void SetBarScale(sf::Vector2f newScale);
    void SetBarColor(sf::Color newColor);

   private:
    void SetAmmo(float current, float max);

    sf::Sprite background;
    sf::Sprite bar;
    std::shared_ptr<UiTextElement> firstText;
    std::shared_ptr<UiTextElement> secondText;
    int currentAmmo = 0;
    int maxAmmo = 0;

    EngineCore::GameObject* playerGameObject = nullptr;
    sf::IntRect barRectOriginal;
    sf::Vector2f ammoBarPosition;
    sf::Vector2f ammoBarScale;
    sf::Color ammoBarColor;
};

class UiImageElement : public UiElement {
   public:
    UiImageElement(const std::string& textureName, sf::IntRect rect,
                   sf::Vector2f position);
    void Update(float deltaTime) override;
    void Render(sf::RenderWindow& window) override;
    void SetElement(sf::IntRect newRect);
    void SetElementPosition(sf::Vector2f newPosition);
    void SetElementScale(sf::Vector2f newScale);
    void SetElementColor(sf::Color newColor);

   private:
    sf::IntRect elementRect;
    sf::Vector2f elementPosition;
    sf::Vector2f elementScale;
    sf::Color elementColor;
};



}  // namespace Rogalique