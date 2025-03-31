#pragma once
#include "Block.h"
#include <vector>
#include <string>
#include <memory>
#include <map>


namespace Arkanoid {

	enum class BlockType
	{
		Simple,
		ThreeHit,
		Unbreackable,
	};
	enum class BonusType {
		FireBall,
		GlassBlocks,
		LongerPlate,
	};

	struct Level {
		std::vector<std::pair<sf::Vector2i,BlockType>> m_blocks;
		std::vector<std::pair<sf::Vector2i, BonusType>> m_bonuses;
	};

	class LevelLoader final
	{
	public:
		LevelLoader() { LoadLevelsFromFile(); };
		Level& GetLevel(int i);
		~LevelLoader() = default;
		int GetLevelCount();
	private:
		void LoadLevelsFromFile();

		std::vector<Level> levels;
		static BlockType CharToBlockType(char symbol);
	};

}

