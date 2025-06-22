#include "DeveloperLevel.h"
#include "Engine.h"
#include "Matrix2D.h"
#include "Player.h"
#include "ResourceSystem.h"
#include "GameSettings.h"
#include <SFML/Graphics.hpp>

using namespace Rogalique;

int main() {
    EngineCore::Engine::Instance();
    LOG_INFO("Setup Logger init!");
    EngineCore::RenderSystem::Instance()->SetMainWindow(
        new sf::RenderWindow(sf::VideoMode(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT), SETTINGS.GAME_NAME));
    
    EngineCore::ResourceSystem::Instance()->LoadTexture(
        "player", SETTINGS.TEXTURES_PATH + "player.png");
    EngineCore::ResourceSystem::Instance()->LoadSound(
        "MetalHell", SETTINGS.SOUNDS_PATH + "MetalHell.wav");
    EngineCore::ResourceSystem::Instance()->LoadTexture(
        "floor", SETTINGS.TEXTURES_PATH + "floor.png");
    EngineCore::ResourceSystem::Instance()->LoadTexture(
        "wall", SETTINGS.TEXTURES_PATH + "wall.png");
    EngineCore::ResourceSystem::Instance()->LoadTexture(
        "cacodemon", SETTINGS.TEXTURES_PATH + "cacodemon.png");
    EngineCore::ResourceSystem::Instance()->LoadTexture(
        "creeper", SETTINGS.TEXTURES_PATH + "creeper.png");
    EngineCore::ResourceSystem::Instance()->LoadTexture(
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
