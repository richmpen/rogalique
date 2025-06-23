#pragma once
#include "Engine.h"

#include <string>

namespace Rogalique {
class GameSettings {
   private:
    GameSettings() = default;

   public:
    static GameSettings& Instance() {
        static GameSettings gameSettings;
        return gameSettings;
    }

    const std::string RESOURCES_PATH = "Assets/";
    const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
    const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
    const unsigned int SCREEN_WIDTH = 1920;
    const unsigned int SCREEN_HEIGHT = 1080;

    // Gameplay
    const float ENEMY_CHASE_DISTANCE = 400.f;
    const float DAMAGE_FLASH_TIMER = 0.5f;
    const float ATTACK_COOLDOWN_DURATION = 1.5f;
    const float CREEPER_EXPLOSION_TIMER = 1.5f;
    // Player
    const int PLAYER_CAMERA_WIDTH = 1920;
    const int PLAYER_CAMERA_HEIGHT = 1080;
    const float PLAYER_SPEED = 1000.f;

    const std::string GAME_NAME = "Rogalique";
    const float TIME_PER_FRAME = 1.f / 60.f;
};
#define SETTINGS GameSettings::Instance()
}  // namespace Rogalique