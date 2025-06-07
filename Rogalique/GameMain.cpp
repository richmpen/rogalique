#include "DeveloperLevel.h"
#include "Engine.h"
#include "Matrix2D.h"
#include "Player.h"
#include "ResourceSystem.h"

#include <SFML/Graphics.hpp>

using namespace Rogalique;

int main() {
    EngineCore::Engine::Instance();
    LOG_INFO("Setup Logger init!");
    EngineCore::RenderSystem::Instance()->SetMainWindow(
        new sf::RenderWindow(sf::VideoMode(1920, 1080), "Rogalique"));

    EngineCore::ResourceSystem::Instance()->LoadTexture(
        "player", "Resources/Textures/player.png");
    EngineCore::ResourceSystem::Instance()->LoadTexture(
        "enemy", "Resources/Textures/enemy.png");
    EngineCore::ResourceSystem::Instance()->LoadSound(
        "soundtrack", "Resources/Sounds/soundtrack.wav");
    EngineCore::ResourceSystem::Instance()->LoadSound(
        "fightMusic", "Resources/Sounds/fightMusic.wav");
    EngineCore::ResourceSystem::Instance()->LoadTexture(
        "floor", "Resources/Textures/floor.png");
    EngineCore::ResourceSystem::Instance()->LoadTexture(
        "wall", "Resources/Textures/wall.png");
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
