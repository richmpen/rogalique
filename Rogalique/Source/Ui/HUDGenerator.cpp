#include "HUDGenerator.h"

#include "GameSettings.h"
#include "InventorySystem.h"
#include "Ui/UiElements/AmmoBarUI.h"
#include "Ui/UiElements/ArmorBarUI.h"
#include "Ui/UiElements/HealthBarUI.h"
#include "Ui/UiElements/ImageUI.h"
#include "Ui/UiElements/QuickSlotsUI.h"
#include "Ui/UiElements/TextUI.h"

namespace Rogalique {
HUDGenerator::HUDGenerator(UiManager* manager,
                           EngineCore::GameObject* gameObject)
    : gameObject(gameObject), uiManager(manager) {}

void HUDGenerator::Generate() {
    if (uiManager) {
        auto healthBar = std::make_shared<HealthBarUI>(
            "UiMap", sf::IntRect(789, 1204, 700, 80),
            sf::IntRect(789, 1120, 700, 80),
            sf::Vector2f(10, SETTINGS.PLAYER_CAMERA_HEIGHT - 150),
            sf::Vector2f(0.8, 0.8), gameObject

        );
        uiManager->AddElement(healthBar);

        auto armorBar = std::make_shared<ArmorBarUI>(
            "UiMap", sf::IntRect(789, 1204, 700, 80),
            sf::IntRect(789, 1120, 700, 80),
            sf::Vector2f(25, SETTINGS.PLAYER_CAMERA_HEIGHT - 100),
            sf::Vector2f(0.72, 0.72), gameObject);
        uiManager->AddElement(armorBar);

        auto healthIcon = std::make_shared<ImageUI>(
            "UiMap", sf::IntRect(777, 2382, 235, 235),
            sf::Vector2f(20, SETTINGS.PLAYER_CAMERA_HEIGHT - 150));
        healthIcon->SetColor(sf::Color(13, 165, 245));
        healthIcon->SetScale(sf::Vector2f{0.25, 0.25});
        uiManager->AddElement(healthIcon);

        auto armorIcon = std::make_shared<ImageUI>(
            "UiMap", sf::IntRect(0, 2382, 235, 235),
            sf::Vector2f(20, SETTINGS.PLAYER_CAMERA_HEIGHT - 100));
        armorIcon->SetColor(sf::Color(15, 191, 6));
        armorIcon->SetScale(sf::Vector2f{0.25, 0.25});
        uiManager->AddElement(armorIcon);

        auto ammoIcon = std::make_shared<ImageUI>(
            "UiMap", sf::IntRect(0, 2382, 235, 235),
            sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH - 100,
                         SETTINGS.PLAYER_CAMERA_HEIGHT - 105));
        ammoIcon->SetColor(sf::Color(221, 204, 136));
        ammoIcon->SetScale(sf::Vector2f{0.25, 0.25});
        uiManager->AddElement(ammoIcon);

        auto ammoIconSecond = std::make_shared<ImageUI>(
            "UiMap", sf::IntRect(3, 700, 210, 180),
            sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH - 240,
                         SETTINGS.PLAYER_CAMERA_HEIGHT - 93));
        ammoIconSecond->SetColor(sf::Color(221, 204, 136));
        ammoIconSecond->SetScale(sf::Vector2f{0.4, 0.4});

        auto ammoTextFirst = std::make_shared<TextUI>(
            48,
            sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH - 225,
                         SETTINGS.PLAYER_CAMERA_HEIGHT - 87),
            true);
        ammoTextFirst->SetColor(sf::Color(221, 204, 136));
        ammoTextFirst->SetStyle(sf::Text::Bold);

        auto ammoTextSecond = std::make_shared<TextUI>(
            24,
            sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH - 158,
                         SETTINGS.PLAYER_CAMERA_HEIGHT - 92),
            false);
        ammoTextSecond->SetColor(sf::Color(105, 97, 64));
        ammoTextSecond->SetStyle(sf::Text::Italic);

        auto ammoBar = std::make_shared<AmmoBarUI>(
            "UiMap", sf::IntRect(789, 1204, 700, 80),
            sf::IntRect(791, 1060, 562, 58), ammoTextFirst, ammoTextSecond,
            sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH - 600,
                         SETTINGS.PLAYER_CAMERA_HEIGHT - 100),
            sf::Vector2f(0.72, 0.72), gameObject);
        uiManager->AddElement(ammoBar);

        uiManager->AddElement(ammoIconSecond);

        uiManager->AddElement(ammoTextFirst);

        auto quickSlots = std::make_shared<QuickSlotsUI>();
        uiManager->AddElement(quickSlots);
    }
}
}  // namespace Rogalique