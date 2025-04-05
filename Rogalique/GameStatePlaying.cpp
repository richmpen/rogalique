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
#include "LevelLoader.h"
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

        blockFactories.emplace(BlockType::Simple, std::make_unique<SimpleBlockFactory>());
        blockFactories.emplace(BlockType::ThreeHit, std::make_unique<ThreeHitBlockFactory>());
        blockFactories.emplace(BlockType::Unbreackable, std::make_unique<UnbreackableBlockFactory>());

        bonusFactories.emplace(BonusType::FireBall, std::make_unique<FireBallBonusFactory>());
        bonusFactories.emplace(BonusType::GlassBlocks, std::make_unique<GlassBlocksBonusFactory>());
        bonusFactories.emplace(BonusType::LongerPlate, std::make_unique<LongerPlateBonusFactory>());

        InitSprite(backgroundSprite, backgroundWidth, backgroundHeight, backgroundTexture);
        backgroundSprite.setPosition(0, 0);
        InitSprite(heartSprite, 50, 50, heartTexture);

        gameObjects.emplace_back(std::make_shared<Plate>(sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATE_HEIGHT / 2)));
        Plate* plate = (Plate*)gameObjects.back().get();
        auto ball = std::make_shared<Ball>(sf::Vector2f(plate->GetPosition().x, plate->GetPosition().y - 75.f));
        ball->AddObserver(weak_from_this());
        gameObjects.emplace_back(ball);

        gameStart = false;

        SpawnBlocks();
        SavePlayingState();

        ScoreSystem::Instance().SetScore(0);
        hp = SETTINGS.PLAYER_HP_AT_LEVEL;

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
        currentState.platePosition = std::dynamic_pointer_cast<Plate>(gameObjects[0])->GetPosition();
        currentState.ballPosition = std::dynamic_pointer_cast<Ball>(gameObjects[1])->GetPosition();
        currentState.blocks = blocks;
        currentState.score = ScoreSystem::Instance().GetScore();
        currentState.bonuses.clear();
        for (const auto& bonus : bonuses) {
            if (!bonus->IsActive()) {
                currentState.bonuses.emplace_back(bonus->GetType(), bonus->GetPosition());
            }
        }
        return Memento::Create(currentState);
    }

    void GameStatePlaying::RestoreMemento(const std::unique_ptr<Memento>& memento) {
        if (!memento) return;
        LevelState restoredState = memento->getState();

        gameStart = false;
        blocks = restoredState.blocks;
        ScoreSystem::Instance().SetScore(restoredState.score);

        for (const auto& effect : activeEffects) {
            effect->FinalAction();
        }
        activeEffects.clear();
        bonuses.clear();

        breackableBlocksCount = 0;
        for (const auto& pair : blockFactories) {
            breackableBlocksCount += pair.second->GetcreatedBreackableBlocksCount();
        }
        for (const auto& block : blocks) {
            if (block->isDestroyed()) {
                --breackableBlocksCount;
            }
        }
    }

    void GameStatePlaying::SavePlayingState()
    {
        initialState = CreateMemento();
    }

    void GameStatePlaying::RestorePlayingState() {
        if (hp > 0) {
            --hp;
            RestoreMemento(initialState);

            std::shared_ptr<Plate> plate = std::dynamic_pointer_cast<Plate>(gameObjects[0]);
            std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
            ball->SetPositionOnPlate(sf::Vector2f(plate->GetPosition().x, plate->GetPosition().y - 75.f));

            for (auto& bonus : bonuses) {
                if (bonus->IsActive()) {
                    bonus->FinalAction();
                }
            }
            if (hp <= 0) {
                gameOverSound.play();
                Application::Instance().GetGame().LooseGame();
            }
            else {
                hpLossSound.play();
            }
        }
    }

    void GameStatePlaying::Update(float timeDelta) {
        hpText.setString(std::to_string(hp));

        static auto updateFunctor = [timeDelta](auto obj) { obj->Update(timeDelta); };

        std::for_each(gameObjects.begin(), gameObjects.end(), updateFunctor);
        std::for_each(blocks.begin(), blocks.end(), updateFunctor);
        std::for_each(bonuses.begin(), bonuses.end(), updateFunctor);

        for (auto& effect : activeEffects) {
            effect->Update(timeDelta);
        }

        activeEffects.erase(
            std::remove_if(activeEffects.begin(), activeEffects.end(),
                [](const auto& effect) { return !effect->IsTimerStarted(); }),
            activeEffects.end()
        );

        std::shared_ptr<Plate> plate = std::dynamic_pointer_cast<Plate>(gameObjects[0]);
        std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
        BackgroundMove(timeDelta);

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            gameStart = true;
        }
        if (gameStart) {
            ball->Update(timeDelta);
        }
        else {
            ball->SetPositionOnPlate(sf::Vector2f(plate->GetPosition().x, plate->GetPosition().y - 75.f));
        }

        auto isCollision = plate->CheckCollision(ball);

        bool needInverseDirX = false;
        bool needInverseDirY = false;
        bool hasBrokeOneBlock = false;

        blocks.erase(
            std::remove_if(blocks.begin(), blocks.end(),
                [ball, &hasBrokeOneBlock, &needInverseDirX, &needInverseDirY, this](const auto& block) {
                    if ((!hasBrokeOneBlock) && block->CheckCollision(ball)) {
                        hasBrokeOneBlock = true;
                        const auto ballPos = ball->GetPosition();
                        const auto blockRect = block->GetRect();
                       
                        GetBallInverse(ballPos, blockRect, needInverseDirX, needInverseDirY);
                        ballSound.play();

                        if (rand() % 10 == 0 && block->GetHitcount() <= 0) {
                            std::vector<BonusType> bonusTypes = { BonusType::FireBall, BonusType::GlassBlocks, BonusType::LongerPlate };
                            BonusType randomBonusType = bonusTypes[rand() % bonusTypes.size()];
                            bonuses.emplace_back(bonusFactories[randomBonusType]->CreateBonus(block->GetPosition()));
                        }
                    }
                    return block->isDestroyed();
                }),
            blocks.end()
        );

        bonuses.erase(
            std::remove_if(bonuses.begin(), bonuses.end(),
                [this, plate, ball](const auto& bonus) {
                    if (bonus->GetCollision(plate)) {
                        bonusEatSound.play();
                        bool bonusAlreadyActive = false;
                        for (auto& effect : activeEffects) {
                            BonusEffect* bonusEffect = dynamic_cast<BonusEffect*>(effect.get());
                            if (bonusEffect && bonusEffect->GetBonusType() == bonus->GetType()) {
                                bonusEffect->ResetTimer(SETTINGS.BONUS_EFFECT_DELAY);
                                bonusAlreadyActive = true;
                                break;
                            }
                        }

                        if (!bonusAlreadyActive) {
                            auto effect = std::make_shared<BonusEffect>(
                                SETTINGS.BONUS_EFFECT_DELAY,
                                bonus,
                                plate,
                                ball,
                                blocks);
                            activeEffects.push_back(effect);
                        }

                        return true;
                    }
                    return bonus->GetPosition().y > SETTINGS.SCREEN_HEIGHT && !bonus->IsActive();
                }),
            bonuses.end()
        );

        if (needInverseDirX) {
            ball->Turning(Turn::X);
        }
        if (needInverseDirY) {
            ball->Turning(Turn::Y);
        }

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
        window.draw(backgroundSprite);



        static auto drawFunc = [&window](auto block) { block->Draw(window); };
        std::for_each(gameObjects.begin(), gameObjects.end(), drawFunc);
        std::for_each(blocks.begin(), blocks.end(), drawFunc);
        std::for_each(bonuses.begin(), bonuses.end(), [&window](auto bonus) { bonus->Draw(window); });

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

    void GameStatePlaying::BackgroundMove(float timeDelta)
    {
        if (bgMoveRight)
        {
            backgroundSprite.setPosition(backgroundSprite.getPosition().x - backgroundSpeed * timeDelta, backgroundSprite.getPosition().y);
            if (backgroundSprite.getPosition().x <= -(backgroundWidth / 2 - SETTINGS.SCREEN_WIDTH))
            {
                bgMoveRight = false;
            }
        }
        else
        {
            backgroundSprite.setPosition(backgroundSprite.getPosition().x + backgroundSpeed * timeDelta, backgroundSprite.getPosition().y);
            if (backgroundSprite.getPosition().x >= (backgroundWidth / 2 - SETTINGS.SCREEN_WIDTH))
            {
                bgMoveRight = true;
            }
        }
    }

    void GameStatePlaying::LoadNextLevel() {
        Game& game = Application::Instance().GetGame();
        if (currentLevel >= levelLoader.GetLevelCount() - 1) {
            ScoreSystem::Instance().SetTotalScore(ScoreSystem::Instance().GetScore());
            gameWinSound.play();
            game.WinGame();
        }
        else {
            ScoreSystem::Instance().SetTotalScore(ScoreSystem::Instance().GetScore());
            ScoreSystem::Instance().SetScore(0);
            std::shared_ptr<Plate> platform = std::dynamic_pointer_cast<Plate>(gameObjects[0]);
            std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
            platform->restart();
            ball->restart();
            ball->SetFireBall(false);
            platform->SetLonger(false);
            for (const auto& block : blocks) {
                block->SetFragile(false);
            }

            blocks.clear();
            ++currentLevel;
            SpawnBlocks();
            SavePlayingState();
            gameStart = false;

            for (auto& effect : activeEffects) {
                effect->FinalAction();
            }
            activeEffects.clear();
            bonuses.clear();
        }
    }

    void GameStatePlaying::SpawnBlocks()
    {
        for (const auto& pair : blockFactories) {
            pair.second->ClearCounter();
        }

        auto self = weak_from_this();
        auto level = levelLoader.GetLevel(currentLevel);

        for (auto pairPosBlockType : level.m_blocks) {
            auto blockType = pairPosBlockType.second;
            sf::Vector2i pos = pairPosBlockType.first;

            sf::Vector2f position{
                (float)(SETTINGS.BLOCK_SHIFT + SETTINGS.BLOCK_WIDTH / 2.f + pos.x * (SETTINGS.BLOCK_WIDTH + SETTINGS.BLOCK_SHIFT))
                , (float)pos.y * SETTINGS.BLOCK_HEIGHT
            };

            blocks.emplace_back(blockFactories[blockType]->CreateBlock(position));
            blocks.back()->AddObserver(self);
        }

        for (const auto& pair : blockFactories) {
            breackableBlocksCount += pair.second->GetcreatedBreackableBlocksCount();
        }
    }

    void GameStatePlaying::GetBonus()
    {
        auto level = levelLoader.GetLevel(currentLevel);
        for (auto pair : level.m_bonuses) {
            sf::Vector2i pos = pair.first;
            auto bonusesType = pair.second;
            sf::Vector2f position{
                (float)(SETTINGS.BLOCK_SHIFT + SETTINGS.BLOCK_WIDTH / 2.f + pos.x * (SETTINGS.BLOCK_WIDTH + SETTINGS.BLOCK_SHIFT))
                    , (float)pos.y * SETTINGS.BLOCK_HEIGHT
            };
            bonuses.emplace_back(bonusFactories[bonusesType]->CreateBonus(position));
        }

    }


    void GameStatePlaying::Notify(std::shared_ptr<IObservable> observable)
    {
        if (auto block = std::dynamic_pointer_cast<Block>(observable); block) {
            Game& game = Application::Instance().GetGame();
            ScoreSystem::Instance().SetScore(ScoreSystem::Instance().GetScore() + block->GetScoreValue());
            --breackableBlocksCount;
            SavePlayingState();
            if (breackableBlocksCount == 0) {
                needLoadNextLevel = true;
            }
        }
        else if (auto ball = std::dynamic_pointer_cast<Ball>(observable); ball)
        {
            if (ball->GetPosition().y > gameObjects.front()->GetRect().top) {
                RestorePlayingState();
            }
        }
    }

    void GameStatePlaying::GetBallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& needInverseDirX, bool& needInverseDirY)
    {
        
        if (ballPos.y > blockRect.top + blockRect.height)
        {
            needInverseDirY = true;
        }
        if (ballPos.x < blockRect.left)
        {
            needInverseDirX = true;
        }
        if (ballPos.x > blockRect.left + blockRect.width)
        {
            needInverseDirX = true;
        }
    }
}

