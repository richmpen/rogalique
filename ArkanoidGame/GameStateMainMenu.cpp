#include "GameStateMainMenu.h"
#include "Application.h"
#include "Game.h"
#include <assert.h>

#include "ScoreSystem.h"

namespace Rogalique
{
	void GameStateMainMenu::Init()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Alata-Regular.ttf"));
		assert(backgroundTexture.loadFromFile(SETTINGS.TEXTURES_PATH + "main-menu-Bg.png"));
		InitSprite(background, SETTINGS.SCREEN_WIDTH,SETTINGS.SCREEN_HEIGHT, backgroundTexture);
		background.setPosition(SETTINGS.SCREEN_WIDTH / 2, SETTINGS.SCREEN_HEIGHT / 2);
		
		MenuItem startGame;
		startGame.text.setString("Start Game");
		startGame.text.setFont(font);
		startGame.text.setCharacterSize(32);
		startGame.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().StartGame();
			};
		
		const bool isInfiniteApples = Application::Instance().GetGame().IsEnableOptions(GameOptions::InfiniteApples);
		MenuItem optionsInfiniteApplesItem;
		optionsInfiniteApplesItem.text.setString("Infinite Apples: " + std::string(isInfiniteApples ? "On" : "Off"));
		optionsInfiniteApplesItem.text.setFont(font);
		optionsInfiniteApplesItem.text.setCharacterSize(32);
		optionsInfiniteApplesItem.onPressCallback = [](MenuItem& item) {
			Game& game = Application::Instance().GetGame();
			bool newOptionValue = !game.IsEnableOptions(GameOptions::InfiniteApples);
			game.SetOption(GameOptions::InfiniteApples, newOptionValue);
			item.text.setString("Infinite Apples: " + std::string(newOptionValue ? "On" : "Off"));
			};

		const bool isWithAcceleration = Application::Instance().GetGame().IsEnableOptions(GameOptions::WithAcceleration);
		MenuItem optionsWithAccelerationItem;
		optionsWithAccelerationItem.text.setString("With Acceleration: " + std::string(isWithAcceleration ? "On" : "Off"));
		optionsWithAccelerationItem.text.setFont(font);
		optionsWithAccelerationItem.text.setCharacterSize(32);
		optionsWithAccelerationItem.onPressCallback = [](MenuItem& item) {
			Game& game = Application::Instance().GetGame();
			bool newOptionValue = !game.IsEnableOptions(GameOptions::WithAcceleration);
			game.SetOption(GameOptions::WithAcceleration, newOptionValue);
			item.text.setString("With Acceleration: " + std::string(newOptionValue ? "On" : "Off"));
			};

		MenuItem options;
		options.text.setString("Options");
		options.text.setFont(font);
		options.text.setCharacterSize(32);
		options.hintText.setString("Options");
		options.hintText.setFont(font);
		options.hintText.setCharacterSize(48);
		options.hintText.setFillColor(sf::Color::White);
		options.childrenOrientation = Orientation::Vertical;
		options.childrenAlignment = Alignment::Middle;
		options.childrenSpacing = 10.f;
		options.childrens.push_back(optionsInfiniteApplesItem);
		options.childrens.push_back(optionsWithAccelerationItem);
		
		MenuItem recordsItem;
		recordsItem.text.setString("Records");
		recordsItem.text.setFont(font);
		recordsItem.text.setCharacterSize(32);
		recordsItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().ShowRecords();
			};

		MenuItem yesItem;
		yesItem.text.setString("Yes");
		yesItem.text.setFont(font);
		yesItem.text.setCharacterSize(32);
		yesItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().QuitGame();
			};

		MenuItem noItem;
		noItem.text.setString("No");
		noItem.text.setFont(font);
		noItem.text.setCharacterSize(32);
		noItem.onPressCallback = [this](MenuItem&) {
			menu.GoBack();
			};

		MenuItem exitGameItem;
		exitGameItem.text.setString("Exit Game");
		exitGameItem.text.setFont(font);
		exitGameItem.text.setCharacterSize(32);
		exitGameItem.hintText.setString("Are you sure?");
		exitGameItem.hintText.setFont(font);
		exitGameItem.hintText.setCharacterSize(48);
		exitGameItem.hintText.setFillColor(sf::Color::White);
		exitGameItem.childrenOrientation = Orientation::Horizontal;
		exitGameItem.childrenAlignment = Alignment::Middle;
		exitGameItem.childrenSpacing = 10.f;
		exitGameItem.childrens.push_back(yesItem);
		exitGameItem.childrens.push_back(noItem);

		MenuItem mainMenu;
		mainMenu.hintText.setString("ARKANOID");
		mainMenu.hintText.setFont(font);
		mainMenu.hintText.setCharacterSize(38);
		mainMenu.hintText.setFillColor(sf::Color::White);
		mainMenu.hintText.setStyle(sf::Text::Bold);
		mainMenu.childrenOrientation = Orientation::Vertical;
		mainMenu.childrenAlignment = Alignment::Middle;
		mainMenu.childrenSpacing = 20.f;
		mainMenu.childrens.push_back(startGame);
		mainMenu.childrens.push_back(options);
		mainMenu.childrens.push_back(recordsItem);
		mainMenu.childrens.push_back(exitGameItem);

		scoreTotalText.setString("Total Score: " + std::to_string(ScoreSystem::Instance().GetTotalScore()));
		scoreTotalText.setFont(font);
		scoreTotalText.setCharacterSize(25);
		scoreTotalText.setFillColor(sf::Color::White);
		scoreTotalText.setStyle(sf::Text::Bold);
		
		menu.Init(mainMenu);
	}

	void GameStateMainMenu::Shutdown(){}

	void GameStateMainMenu::Control(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				menu.GoBack();
			}
			else if (event.key.code == sf::Keyboard::Enter)
			{
				menu.PressOnSelectedItem();
			}
			
			Orientation orientation = menu.GetCurrentContext().childrenOrientation;
			if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Up ||
				orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Left)
			{
				menu.SwitchToPreviousMenuItem();
			}
			else if (orientation == Orientation::Vertical && event.key.code == sf::Keyboard::Down ||
						orientation == Orientation::Horizontal && event.key.code == sf::Keyboard::Right)
			{
				menu.SwitchToNextMenuItem();
			}
		}
	}

	void GameStateMainMenu::Update(float timeDelta)
	{

	}

	void GameStateMainMenu::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = (sf::Vector2f)window.getView().getSize();
		DrawSprite(background, window);
		sf::Text* hintText = &menu.GetCurrentContext().hintText;
		hintText->setOrigin(GetTextOrigin(*hintText, { 0.5f, 0.f }));
		hintText->setPosition(viewSize.x / 2.f, 150.f);
		window.draw(*hintText);

		scoreTotalText.setOrigin(GetTextOrigin(scoreTotalText, { 0.5f, 1.f }));
		scoreTotalText.setPosition(viewSize.x -120, viewSize.y / 2 - 310.f);
		window.draw(scoreTotalText);

		menu.Draw(window, viewSize / 2.f, { 0.5f, 0.f });
	}

}
