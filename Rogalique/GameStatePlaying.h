#pragma once
#include <unordered_map>
#include <memory>
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "GameStateData.h"
#include "IObserver.h"
#include "ScoreSystem.h"
#include "Memento.h"

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
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;

		std::unique_ptr<Memento> CreateMemento();
		void RestoreMemento(const std::unique_ptr<Memento>& memento);
		void SavePlayingState();
		void RestorePlayingState();
	private:
		bool needLoadNextLevel = false;

		sf::Texture backgroundTexture;
		sf::Texture heartTexture;
		sf::Font font;
		sf::SoundBuffer ballSoundBuffer;
		sf::SoundBuffer hpLossSoundBuffer;
		sf::SoundBuffer bonusEatSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;
		sf::SoundBuffer gameWinSoundBuffer;

		
		bool gameStart = false;

		sf::Text scoreText;
		sf::Text totalScoreText;
		sf::Text inputHintText;
		sf::Text hpText;
		sf::Vector2f hpInterfacePosition = {40.f, 85.f};
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

		int breackableBlocksCount = 0;

		int currentLevel = 0;
		int hp = 0;
		std::unique_ptr<Memento> initialState;
	};

	 
}
