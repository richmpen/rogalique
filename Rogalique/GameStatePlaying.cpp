#include "GameStatePlaying.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include "Object.h"
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include "ScoreSystem.h"
#include <iostream>
#include "Memento.h"


namespace Rogalique
{
    void GameStatePlaying::Init()
    {
        assert(font.loadFromFile(SETTINGS.FONTS_PATH + "Alata-Regular.ttf"));
        assert(ballSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "ball.wav"));
        assert(hpLossSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "hploss.wav"));
        assert(bonusEatSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "bonus.wav"));
        assert(gameOverSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "Death.wav"));
        assert(gameWinSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "GameWin.wav"));
        assert(backgroundTexture.loadFromFile(SETTINGS.TEXTURES_PATH + "BackgroudnGameScene.jpg"));
        assert(heartTexture.loadFromFile(SETTINGS.TEXTURES_PATH + "heart.png"));

        InitSprite(heartSprite, 50, 50, heartTexture);

        gameStart = false;

        SavePlayingState();

        ScoreSystem::Instance().SetScore(0);

        scoreText.setFont(font);
        scoreText.setCharacterSize(32);
        scoreText.setStyle(sf::Text::Bold);
        scoreText.setFillColor(sf::Color(178, 34, 34));

        totalScoreText.setFont(font);
        totalScoreText.setCharacterSize(22);
        totalScoreText.setFillColor(sf::Color(205, 92, 92));

        hpText.setFont(font);
        hpText.setCharacterSize(22);
        hpText.setFillColor(sf::Color::White);

        inputHintText.setFont(font);
        inputHintText.setCharacterSize(32);
        inputHintText.setFillColor(sf::Color::White);
        inputHintText.setString("Press SPACE to Play \n ESC to pause");
        inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

        ballSound.setBuffer(ballSoundBuffer);
		hpLossSound.setBuffer(hpLossSoundBuffer);
        gameOverSound.setBuffer(gameOverSoundBuffer);
        gameWinSound.setBuffer(gameWinSoundBuffer);
		bonusEatSound.setBuffer(bonusEatSoundBuffer);
    }

    void GameStatePlaying::Shutdown() {}

    void GameStatePlaying::Control(const sf::Event& event)
    {
        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                Application::Instance().GetGame().PauseGame();
            }
        }
    }

    std::unique_ptr<Memento> GameStatePlaying::CreateMemento() {
        LevelState currentState;
        return Memento::Create(currentState);
    }

    void GameStatePlaying::RestoreMemento(const std::unique_ptr<Memento>& memento) {
        if (!memento) return;
        LevelState restoredState = memento->getState();

        gameStart = false;
    }

    void GameStatePlaying::SavePlayingState()
    {
        initialState = CreateMemento();
    }

    void GameStatePlaying::RestorePlayingState() {
        
    }

    void GameStatePlaying::Update(float timeDelta) {

        scoreText.setString("Score: " + std::to_string(ScoreSystem::Instance().GetScore()));
        totalScoreText.setString("Total score: " + std::to_string(ScoreSystem::Instance().GetTotalScore()));

        if (needLoadNextLevel) {
            needLoadNextLevel = false;
            Game& game = Application::Instance().GetGame();
            game.LoadNextLevel();
        }
    }

    void GameStatePlaying::Draw(sf::RenderWindow& window)
    {
        scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
        scoreText.setPosition(10.f, 10.f);
        window.draw(scoreText);

        totalScoreText.setOrigin(GetTextOrigin(totalScoreText, { 0.f, 0.f }));
        totalScoreText.setPosition(200.f, 18.f);
        window.draw(totalScoreText);

        sf::Vector2f viewSize = window.getView().getSize();
        inputHintText.setPosition(viewSize.x - 10.f, 10.f);
        window.draw(inputHintText);
        heartSprite.setPosition(hpInterfacePosition);
        window.draw(heartSprite);
        hpText.setOrigin(GetTextOrigin(hpText, { 0.5f, 0.7f }));
        hpText.setPosition(hpInterfacePosition);
        window.draw(hpText);
    }


    void GameStatePlaying::LoadNextLevel() {
       
    }


    void GameStatePlaying::Notify(std::shared_ptr<IObservable> observable)
    {}

}

