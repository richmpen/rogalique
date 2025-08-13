#include "AmmoBarUI.h"

#include "AmmoComponent.h"

namespace Rogalique {
AmmoBarUI::AmmoBarUI(const std::string& textureName, sf::IntRect bgRect,
                     sf::IntRect barRect, std::shared_ptr<TextUI> firstText,
                     std::shared_ptr<TextUI> secondText, sf::Vector2f position,
                     sf::Vector2f barScale, EngineCore::GameObject* player)
    : rect(barRect),
      playerGameObject(player),
      scale(barScale),
      firstText(firstText),
      secondText(secondText) {
    font.loadFromFile(SETTINGS.FONTS_PATH + "roboto/Roboto-Medium.ttf");

    const sf::Texture* tex =
        EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName);
    if (tex) {
        background.setTexture(*tex);
        background.setTextureRect(bgRect);
        background.setPosition(position);
        background.setColor(sf::Color(221, 204, 136));
        background.setScale(scale);

        bar.setTexture(*tex);
        bar.setTextureRect(barRect);
        bar.setPosition(position);
        bar.setColor(sf::Color(248, 255, 156));
        bar.setScale(scale);
    }
}

void AmmoBarUI::SetAmmo(float current, float max) {
    currentAmmo = current;
    maxAmmo = max;
    float percent = (max > 0) ? (current / max) : 0.f;
    int newWidth = static_cast<int>(rect.width * percent);
    sf::IntRect newRect = rect;
    newRect.width = newWidth > 0 ? newWidth : 0;
    bar.setTextureRect(newRect);
}

void AmmoBarUI::Update(float deltaTime) {
    if (!playerGameObject) return;
    auto ammoComponent = playerGameObject->GetComponent<AmmoComponent>();
    if (!ammoComponent) return;
    float current = static_cast<float>(ammoComponent->GetAmmo());
    float max = static_cast<float>(ammoComponent->GetMaxAmmo());
    int ammoInClip = ammoComponent->GetAmmoInClip();
    SetAmmo(current, max);
    firstText->SetText(std::to_string(currentAmmo), false);
    secondText->SetText(std::to_string(ammoInClip), false);
}
void AmmoBarUI::Render(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(bar);
    if (firstText) {
        firstText->Render(window);
    }
    if (secondText) {
        secondText->Render(window);
    }
}
}  // namespace Rogalique