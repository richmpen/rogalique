#include "ButtonUI.h"
#include "RenderSystem.h"
#include "ResourceSystem.h"

namespace Rogalique {
    
    ButtonUI::ButtonUI(const std::string& text, const std::string& textureName, sf::IntRect rect, sf::Vector2f position, sf::Vector2f size, sf::Color color)
: text(text), elementRect(rect), elementPosition(position), elementScale(1.0f, 1.0f), originInCenter(true){
        
        SetTextureFromMap(textureName, rect);
        SetPosition(position);
        SetElementColor(color);
        SetElementSize(size);
        
        // Text setup
        buttonText = std::make_shared<TextUI>(24, sf::Vector2f(position.x, position.y-5),false);
        buttonText->SetText(text, true);
        buttonText->SetColor(sf::Color::White);
        
        
        bounds = sprite.getGlobalBounds();
    }
    
    void ButtonUI::Update(float deltaTime) {
        bounds = sprite.getGlobalBounds();
        
        if (!isEnabled) {
            sprite.setColor(disabledColor);
            return;
        }
        // Update color based on state
        if (isPressed) {
            sprite.setColor(pressColor);
        } else if (isHovered) {
            sprite.setColor(hoverColor);
        } else {
            sprite.setColor(color);
        }
    }
    
    void ButtonUI::Render(sf::RenderWindow& window) {
        window.draw(sprite);
        
        if (buttonText) {
            buttonText->Render(window);
        }
    }
    
    bool ButtonUI::HandleEvent(const sf::Event& event) {
        if (!isEnabled || !isActive) return false;
        
        auto& window = EngineCore::RenderSystem::Instance()->GetMainWindow();
        
        
        auto oldView = window.getView();
        window.setView(window.getDefaultView());
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        window.setView(oldView);
        

        bool wasHovered = isHovered;
        isHovered = bounds.contains(mousePos);
        
       
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left && isHovered) {
                isPressed = true;
                return true;
            }
        } else if (event.type == sf::Event::MouseButtonReleased) {
            if (event.mouseButton.button == sf::Mouse::Left && isPressed) {
                isPressed = false;
                if (isHovered && onClick) {
                    onClick();
                }
                return true;
            }
        }
        
        return false;
    }
    
    void ButtonUI::SetText(const std::string& text, bool setOrigin) {
        if (buttonText) {
            buttonText->SetText(text, setOrigin);
        }
    }
    
    void ButtonUI::SetElementPosition(sf::Vector2f newPosition) {
        elementPosition = newPosition;
        SetPosition(newPosition);
        
        if (buttonText) {
            buttonText->SetPosition(newPosition);
        }
        
        bounds = sprite.getGlobalBounds();
    }
    
    void ButtonUI::SetElementScale(sf::Vector2f newScale) {
        elementScale = newScale;
        SetScale(newScale);
        bounds = sprite.getGlobalBounds();
    }
    
    void ButtonUI::SetElementSize(sf::Vector2f size) {
        
        sf::Vector2f textureSize(static_cast<float>(elementRect.width), static_cast<float>(elementRect.height));
        sf::Vector2f scale(size.x / textureSize.x, size.y / textureSize.y);
        SetElementScale(scale);
    }
    
    void ButtonUI::SetElementColor(sf::Color newColor) {
        color = newColor;
        SetColor(newColor);
    }
    
    void ButtonUI::SetElementOriginCenter() {
        SetCenterOrigin();
        bounds = sprite.getGlobalBounds();
    }
}