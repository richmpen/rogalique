#pragma once
#include <string>

namespace Rogalique
{
	class GameWorld
	{
	public:
		static GameWorld& Instance()
		{
			static GameWorld gameWorld;
			return gameWorld;
		}
	
		GameWorld() = default;
		
		const std::string RESOURCES_PATH = "Resources/";
		const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
		const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
		const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
		const std::string LEVELS_CONFIG_PATH = RESOURCES_PATH + "levels.config";
		const std::string SCORE_CONFIG_PATH = RESOURCES_PATH + "score.config";
		const unsigned int SCREEN_WIDTH = 1280;
		const unsigned int SCREEN_HEIGHT = 720;

		const float TIME_PER_FRAME = 1.f / 60.f;
		
		const int MAX_RECORDS_TABLE_SIZE = 5;
		const char* PLAYER_ID = "Richmpen - Player";

		const std::string GAME_NAME = "Rogalique";
		const std::string NOTIFICATION = "TO BE DONE… \n Press Esc to exit to menu";
	};
#define SETTINGS GameWorld::Instance()
}