#pragma once
#include <string>

namespace Arkanoid
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

		const int PLAYER_HP_AT_LEVEL = 3;

		const int BLOCKS_COUNT_ROWS = 4;
		const int BLOCKS_COUNT_IN_ROW = 12;
		
		const int WIN_SCORE = BLOCKS_COUNT_ROWS*BLOCKS_COUNT_IN_ROW;
		const float TIME_PER_FRAME = 1.f / 60.f;
		
		const unsigned int BLOCK_SHIFT = 5;
		const float BLOCK_WIDTH = (SCREEN_WIDTH - (BLOCKS_COUNT_IN_ROW + 1) * BLOCK_SHIFT) / BLOCKS_COUNT_IN_ROW;
		const float BLOCK_HEIGHT = 50.f;

		const float BREAK_DELAY = 0.5f;
		const int CRUMBLING_HEALTH = 3;

		const int BALL_SIMPLE_BLOCK_SCORE = 5;
		const int BALL_UNBREACKABLE_BLOCK_SCORE = 30;
		const int BALL_THREE_HIT_BLOCK_SCORE = 15;
		
		const float BALL_SIZE = 50.f;
		const float BALL_SPEED = 300.f;
		
		const float PLATE_WIDTH = 200.f;
		const float PLATE_HEIGHT = 50.f;
		const float PLATE_SPEED = 10.0f;

		const float BONUS_SIZE = 50.f;
		const float BONUS_SPEED = 100.f;
		const float BONUS_EFFECT_DELAY = 10.f;
		
		const int MAX_RECORDS_TABLE_SIZE = 5;
		const char* PLAYER_ID = "Richmpen - Player";

		const std::string GAME_NAME = "Arkanoid";
	};
#define SETTINGS GameWorld::Instance()
}