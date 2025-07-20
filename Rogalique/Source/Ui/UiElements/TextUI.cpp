#include "TextUI.h"
#include "GameSettings.h"

namespace Rogalique {
TextUI::TextUI(int size, sf::Vector2f position, bool bold) {
    firstFont = EngineCore::ResourceSystem::Instance()->GetFont("normalFont");
    secondFont = EngineCore::ResourceSystem::Instance()->GetFont("boldFont");
    if (!bold) {
        text.setFont(*firstFont);
    }else {
        text.setFont(*secondFont);
    }
    
    text.setCharacterSize(size);
    text.setPosition(position);
    
}

void TextUI::Render(sf::RenderWindow& window) { window.draw(text); }

void TextUI::SetText(const std::string& newText, bool setOrigin) {
    text.setString(newText);
    if (setOrigin) {
        SetTextOrigin();
    }
}

void TextUI::SetPosition(sf::Vector2f newPosition) {
    text.setPosition(newPosition);
}

void TextUI::SetColor(sf::Color newColor) {
    text.setFillColor(newColor);
}

void TextUI::SetSize(int newSize) { text.setCharacterSize(newSize); }

void TextUI::SetStyle(sf::Text::Style style) { text.setStyle(style); }

void TextUI::SetTextOrigin() {
    sf::FloatRect rc = text.getLocalBounds();
    text.setOrigin(rc.width/2, rc.height/2);
}
const sf::Font* TextUI::GetFirstFont() {
    return firstFont;
}

const sf::Font* TextUI::GetSecondFont() {
    return secondFont;
}
}