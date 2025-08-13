#include "DeveloperLevel.h"
#include "Engine.h"
#include "GameSettings.h"
#include "GameStateManager.h"
#include "Matrix2D.h"
#include "Player.h"
#include "ResourceSystem.h"
#include "States/InventoryState.h"
#include "States/MainMenuState.h"

#include <SFML/Graphics.hpp>

using namespace Rogalique;

int main() {
    EngineCore::Engine::Instance();
    LOG_INFO("Setup Logger init!");
    EngineCore::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(
        sf::VideoMode(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT),
        SETTINGS.GAME_NAME));

    // Load Textures
    ResourceSystem::Instance()->LoadTexture(
        "floor", SETTINGS.TEXTURES_PATH + "floor.png");
    ResourceSystem::Instance()->LoadTexture(
        "wall", SETTINGS.TEXTURES_PATH + "wall.png");
    ResourceSystem::Instance()->LoadTexture(
        "creeperExplosion", SETTINGS.TEXTURES_PATH + "creeperExplosion.png");
    ResourceSystem::Instance()->LoadTexture(
        "menu_bg", SETTINGS.TEXTURES_PATH + "menuBackground.png");
    ResourceSystem::Instance()->LoadTexture(
        "logo", SETTINGS.TEXTURES_PATH + "logo.png");
    ResourceSystem::Instance()->LoadTexture(
        "inventoryPanelMap", SETTINGS.TEXTURES_PATH + "inventoryPanelMap.png");
    ResourceSystem::Instance()->LoadTexture(
        "HealthItem", SETTINGS.TEXTURES_PATH + "PotionRed.png");
    ResourceSystem::Instance()->LoadTexture(
        "ArmorItem", SETTINGS.TEXTURES_PATH + "PotionGreen.png");
    ResourceSystem::Instance()->LoadTexture(
        "AmmoItem", SETTINGS.TEXTURES_PATH + "Backpack.png");
    ResourceSystem::Instance()->LoadTexture(
        "WeaponItem", SETTINGS.TEXTURES_PATH + "SwordT2.png");
    ResourceSystem::Instance()->LoadTexture(
        "UiMap", SETTINGS.TEXTURES_PATH + "UiMap.png");
    ResourceSystem::Instance()->LoadTexture(
        "UiMap2", SETTINGS.TEXTURES_PATH + "UiMap2.png");
    ResourceSystem::Instance()->LoadTexture(
        "panel", SETTINGS.TEXTURES_PATH + "Panel.png");

    // Load TextureMaps
    ResourceSystem::Instance()->LoadTextureMap(
        "playerTMALL", SETTINGS.TEXTURE_MAP_PATH + "PlayerTMALL.png", {64, 64},
        20, true);
    ResourceSystem::Instance()->LoadTextureMap(
        "explosionTM", SETTINGS.TEXTURE_MAP_PATH + "explosionTM.png", {64, 64},
        5, true);
    ResourceSystem::Instance()->LoadTextureMap(
        "cacodemonTM", SETTINGS.TEXTURE_MAP_PATH + "cacodemon.png", {64, 64}, 6,
        true);
    ResourceSystem::Instance()->LoadTextureMap(
        "demonWalk", SETTINGS.TEXTURE_MAP_PATH + "Demon_Walking.png", {64, 64},
        3, true);
    ResourceSystem::Instance()->LoadTextureMap(
        "demonDeath", SETTINGS.TEXTURE_MAP_PATH + "Demon_Death.png", {64, 64},
        6, true);

    // Load Sounds
    ResourceSystem::Instance()->LoadSound(
        "MetalHell", SETTINGS.SOUNDS_PATH + "MetalHell.wav");

    // Load Fonts
    ResourceSystem::Instance()->LoadFont(
        "normalFont", SETTINGS.FONTS_PATH + "EternalUiRegular-BWZGd.ttf");
    ResourceSystem::Instance()->LoadFont(
        "boldFont", SETTINGS.FONTS_PATH + "EternalUiBold-Rpj0A.ttf");

    // First State load
    GameStateManager::Instance()->ChangeState(
        std::make_shared<MainMenuState>());

    EngineCore::Engine::Instance()->Run();

    return 0;
}
