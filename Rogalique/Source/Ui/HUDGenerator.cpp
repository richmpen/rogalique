#include "HUDGenerator.h"

#include "GameSettings.h"

namespace Rogalique {
HUDGenerator::HUDGenerator(const std::shared_ptr<UiManager>& manager, DeveloperLevel* level, GameObject* gameObject) : level(level), gameObject(gameObject), uiManager(manager) {
}

void HUDGenerator::Generate() {
    if (uiManager) {
        
        auto healthBar = std::make_shared<HealthBar>(
            "UiMap",
            sf::IntRect(789, 1204, 700, 80),
            sf::IntRect(789, 1120, 700, 80),
            sf::Vector2f(10, SETTINGS.PLAYER_CAMERA_HEIGHT - 150),
            sf::Vector2f(0.8, 0.8),
            gameObject
            
        );
        uiManager->AddElement(healthBar);
        auto armorBar = std::make_shared<ArmorBar>(
            "UiMap",
            sf::IntRect(789, 1204, 700, 80),
            sf::IntRect(789, 1120, 700, 80),
            sf::Vector2f(25, SETTINGS.PLAYER_CAMERA_HEIGHT - 100),
            sf::Vector2f(0.72, 0.72),
            gameObject
        );
        uiManager->AddElement(armorBar);

        auto ammoBar = std::make_shared<AmmoBar>(
            "UiMap",
            sf::IntRect(789, 1204, 700, 80),
            sf::IntRect(791, 1060, 562, 58),
            sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH - 220, SETTINGS.PLAYER_CAMERA_HEIGHT - 85),
            sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH - 158, SETTINGS.PLAYER_CAMERA_HEIGHT - 92),
            sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH - 600, SETTINGS.PLAYER_CAMERA_HEIGHT - 100),
            sf::Vector2f(0.72, 0.72),
            gameObject
        );
        uiManager->AddElement(ammoBar);
        

        auto healthIcon = std::make_shared<UiImageElement>("UiMap", sf::IntRect(777, 2382, 235, 235), sf::Vector2f(20, SETTINGS.PLAYER_CAMERA_HEIGHT - 150));
        healthIcon->SetElementColor(sf::Color(13,165,245));
        healthIcon->SetElementScale(sf::Vector2f{0.25, 0.25});
        uiManager->AddElement(healthIcon);

        auto armorIcon = std::make_shared<UiImageElement>("UiMap", sf::IntRect(0, 2382, 235, 235), sf::Vector2f(20, SETTINGS.PLAYER_CAMERA_HEIGHT - 100));
        armorIcon->SetElementColor(sf::Color(15, 191,6));
        armorIcon->SetElementScale(sf::Vector2f{0.25, 0.25});
        uiManager->AddElement(armorIcon);

        auto ammoIcon = std::make_shared<UiImageElement>("UiMap", sf::IntRect(0, 2382, 235, 235), sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH-100, SETTINGS.PLAYER_CAMERA_HEIGHT - 105));
        ammoIcon->SetElementColor(sf::Color(221, 204, 136));
        ammoIcon->SetElementScale(sf::Vector2f{0.25, 0.25});
        uiManager->AddElement(ammoIcon);

        // auto ammoIconSecond = std::make_shared<UiImageElement>("UiMap", sf::IntRect(3, 700, 210, 180), sf::Vector2f(SETTINGS.PLAYER_CAMERA_WIDTH - 220, SETTINGS.PLAYER_CAMERA_HEIGHT - 85));
        // ammoIconSecond->SetElementColor(sf::Color(67, 62, 41));
        // ammoIconSecond->SetElementScale(sf::Vector2f{0.25, 0.25});
        // uiManager->AddElement(ammoIconSecond);
    }
}
}