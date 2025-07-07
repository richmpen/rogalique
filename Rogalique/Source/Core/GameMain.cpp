#include "DeveloperLevel.h"
#include "Engine.h"
#include "GameSettings.h"
#include "Matrix2D.h"
#include "Player.h"
#include "ResourceSystem.h"
#include "UiManager.h"

#include <SFML/Graphics.hpp>

using namespace Rogalique;

int main() {
    EngineCore::Engine::Instance();
    LOG_INFO("Setup Logger init!");
    EngineCore::RenderSystem::Instance()->SetMainWindow(new sf::RenderWindow(
        sf::VideoMode(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT),
        SETTINGS.GAME_NAME));

    ResourceSystem::Instance()->LoadTexture(
        "UiMap", SETTINGS.TEXTURES_PATH + "UiMap.png");
    ResourceSystem::Instance()->LoadTextureMap(
        "playerTM", SETTINGS.TEXTURE_MAP_PATH + "PlayerTextureMap.png",
        {64, 64}, 5, true);
    ResourceSystem::Instance()->LoadTextureMap(
        "playerTMALL", SETTINGS.TEXTURE_MAP_PATH + "PlayerTMALL.png", {64, 64},
        20, true);

    ResourceSystem::Instance()->LoadTextureMap(
        "enemyTM", SETTINGS.TEXTURE_MAP_PATH + "enemyTM.png", {64, 64}, 6,
        true);
    ResourceSystem::Instance()->LoadTextureMap(
        "explosionTM", SETTINGS.TEXTURE_MAP_PATH + "explosionTM.png", {64, 64},
        5, true);
    ResourceSystem::Instance()->LoadTextureMap(
        "cacodemonTM", SETTINGS.TEXTURE_MAP_PATH + "cacodemon.png", {64, 64}, 6,
        true);
    ResourceSystem::Instance()->LoadTexture(
        "player", SETTINGS.TEXTURES_PATH + "player.png");
    ResourceSystem::Instance()->LoadSound(
        "MetalHell", SETTINGS.SOUNDS_PATH + "MetalHell.wav");
    ResourceSystem::Instance()->LoadTexture(
        "floor", SETTINGS.TEXTURES_PATH + "floor.png");
    ResourceSystem::Instance()->LoadTexture(
        "wall", SETTINGS.TEXTURES_PATH + "wall.png");
    ResourceSystem::Instance()->LoadTexture(
        "cacodemon", SETTINGS.TEXTURES_PATH + "cacodemon.png");
    ResourceSystem::Instance()->LoadTexture(
        "creeper", SETTINGS.TEXTURES_PATH + "creeper.png");
    ResourceSystem::Instance()->LoadTexture(
        "creeperExplosion", SETTINGS.TEXTURES_PATH + "creeperExplosion.png");
    auto developerLevel = std::make_shared<DeveloperLevel>();
    developerLevel->Start();

    /*EngineCore::Matrix2D zeroMatrix;
    zeroMatrix.Print();*/

    /*EngineCore::Matrix2D translationMatrix =
    EngineCore::Matrix2D(Vector2Df(12.f, 5.f), 0.f, Vector2Df(1.f, 1.f));
    translationMatrix.Print();

    EngineCore::Matrix2D rotationMatrix = EngineCore::Matrix2D(Vector2Df(0.f,
    0.f), 90.f, Vector2Df(1.f, 1.f)); rotationMatrix.Print();

    (rotationMatrix * translationMatrix).Print();

    EngineCore::Matrix2D someMatrix =
    EngineCore::Matrix2D(Vector2Df(13.f, 25.f), 90.f, Vector2Df(1.5f, 1.f));
    someMatrix.Print();

    (someMatrix * someMatrix.GetInversed()).Print();*/

    EngineCore::Engine::Instance()->Run();

    return 0;
}
