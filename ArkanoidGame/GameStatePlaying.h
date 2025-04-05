#pragma once
#include <unordered_map>
#include <memory>
#include "LevelLoader.h"
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Plate.h"
#include "Ball.h"
#include "Bonus.h"
#include "Block.h"
#include "BlockFactory.h"
#include "BonusFactory.h"
#include "GameStateData.h"
#include "IObserver.h"
#include "ScoreSystem.h"
#include "LevelState.h"
#include "Memento.h"
#include "BonusEffect.h"

namespace Rogalique
{
	class ScoreSystem;
	class Game;
	class Block;


	class GameStatePlaying : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlaying>
	{
	public:
		void Init() override;
		void Shutdown() override;
		void Control(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		void GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX, bool& needInverseDirY);
		void BackgroundMove(float timeDelta);
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;

		std::unique_ptr<Memento> CreateMemento();
		void RestoreMemento(const std::unique_ptr<Memento>& memento);
		void SavePlayingState();
		void RestorePlayingState();
	private:
		bool needLoadNextLevel = false;
		void SpawnBlocks();
		void GetBonus();
		std::vector<std::shared_ptr<BonusEffect>> activeEffects;

		sf::Texture backgroundTexture;
		sf::Texture heartTexture;
		sf::Font font;
		sf::SoundBuffer ballSoundBuffer;
		sf::SoundBuffer hpLossSoundBuffer;
		sf::SoundBuffer bonusEatSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::SoundBuffer gameWinSoundBuffer;

		std::vector<std::shared_ptr<Object>> gameObjects;
		std::vector<std::shared_ptr<Block>> blocks;
		std::vector<std::shared_ptr<Bonus>> bonuses;
		bool gameStart = false;

		sf::Text scoreText;
		sf::Text totalScoreText;
		sf::Text inputHintText;
		sf::Text hpText;
		sf::Vector2f hpInterfacePosition = {40.f, 85.f};
		sf::Sprite backgroundSprite;
		sf::Sprite heartSprite;
		float backgroundSpeed = 30.f;
		float backgroundWidth = 7334.f;
		float backgroundHeight = 2200.f;
		bool bgMoveRight = true;

		sf::Sound ballSound;
		sf::Sound hpLossSound;
		sf::Sound bonusEatSound;
		sf::Sound gameOverSound;
		sf::Sound gameWinSound;

		std::unordered_map<BlockType, std::unique_ptr<BlockFactory>> blockFactories;
		int breackableBlocksCount = 0;

		std::unordered_map<BonusType, std::unique_ptr<BonusFactory>> bonusFactories;

		LevelLoader levelLoader;
		int currentLevel = 0;
		int hp = 0;
		std::unique_ptr<Memento> initialState;
	};

	 
}
