#include "GameStateGameWin.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace Rogalique
{
	

	void GameStateGameWin::Init()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Alata-Regular.ttf"));

		timeSinceGameWin = 0.f;

		sf::Color backgroundColor = sf::Color::Black;
		backgroundColor.a = 200;
		background.setFillColor(backgroundColor);

		gameWinText.setFont(font);
		gameWinText.setCharacterSize(48);
		gameWinText.setStyle(sf::Text::Bold);
		gameWinText.setFillColor(sf::Color::Green);
		gameWinText.setString("Game Win!");

		recordsTableTexts.reserve(SETTINGS.MAX_RECORDS_TABLE_SIZE);
		
		scoreTotalText.setFont(font);
		scoreTotalText.setCharacterSize(38);
		scoreTotalText.setStyle(sf::Text::Bold);
		scoreTotalText.setFillColor(sf::Color::Green);
		scoreTotalText.setString("Total Score: " + std::to_string(ScoreSystem::Instance().GetTotalScore()));
		
		std::multimap<int, std::string> sortedRecordsTable;
		Game& game = Application::Instance().GetGame();
		for (const auto& item : game.GetRecordsTable())
		{
			sortedRecordsTable.insert(std::make_pair(item.second, item.first));
		}

		bool isPlayerInTable = false;
		auto it = sortedRecordsTable.rbegin();
		for (int i = 0; i < SETTINGS.MAX_RECORDS_TABLE_SIZE && it != sortedRecordsTable.rend(); ++i, ++it)
		{
			recordsTableTexts.emplace_back();
			sf::Text& text = recordsTableTexts.back();
			
			std::stringstream sstream;
			sstream << i + 1 << ". " << it->second << ": " << it->first;
			text.setString(sstream.str());
			text.setFont(font);
			text.setCharacterSize(24);
			if (it->second == SETTINGS.PLAYER_ID)
			{
				text.setFillColor(sf::Color::Green);
				isPlayerInTable = true;
			}
			else
			{
				text.setFillColor(sf::Color::White);
			}
		}

		if (!isPlayerInTable)
		{
			sf::Text& text = recordsTableTexts.back();
			std::stringstream sstream;
			int playerScores = game.GetRecordByPlayerId(SETTINGS.PLAYER_ID);
			sstream << SETTINGS.MAX_RECORDS_TABLE_SIZE << ". " << SETTINGS.PLAYER_ID << ": " << playerScores;
			text.setString(sstream.str());
			text.setFillColor(sf::Color::Green);
		}

		hintText.setFont(font);
		hintText.setCharacterSize(24);
		hintText.setFillColor(sf::Color::White);
		hintText.setString("Play again?");


		MenuItem exitItem;
		exitItem.text.setString("No");
		exitItem.text.setFont(font);
		exitItem.text.setCharacterSize(32);
		exitItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().ExitGame();
			};

		MenuItem restartItem;
		restartItem.text.setString("Yes");
		restartItem.text.setFont(font);
		restartItem.text.setCharacterSize(32);
		restartItem.onPressCallback = [](MenuItem&) {
			Application::Instance().GetGame().StartGame();
			};

		MenuItem WinMenu;
		WinMenu.childrenOrientation = Orientation::Horizontal;
		WinMenu.childrenAlignment = Alignment::Middle;
		WinMenu.childrenSpacing = 20.f;
		WinMenu.childrens.push_back(restartItem);
		WinMenu.childrens.push_back(exitItem);

		menu.Init(WinMenu);
	}

	void GameStateGameWin::Shutdown() {}

	void GameStateGameWin::Control(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PopState();
			}

			if (event.key.code == sf::Keyboard::Enter)
			{
				menu.PressOnSelectedItem();
			}

			Orientation orientation = menu.GetCurrentContext().childrenOrientation;
			if (event.key.code == sf::Keyboard::Left)
			{
				menu.SwitchToPreviousMenuItem();
			}
			else if (event.key.code == sf::Keyboard::Right)
			{
				menu.SwitchToNextMenuItem();
			}
		}
	}

	void GameStateGameWin::Update(float timeDelta)
	{
		timeSinceGameWin += timeDelta;

		sf::Color gameWinTextColor = (int)timeSinceGameWin % 3 ? sf::Color::Blue : sf::Color::White;
		gameWinText.setFillColor(gameWinTextColor);
		sf::Color scoreTotalTextColor = (int)timeSinceGameWin % 2 ? sf::Color::Red : sf::Color::White;
		scoreTotalText.setFillColor(scoreTotalTextColor);
	}

	void GameStateGameWin::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		background.setOrigin(0.f, 0.f);
		background.setSize(viewSize);
		window.draw(background);
		
		gameWinText.setOrigin(GetTextOrigin(gameWinText, { 0.5f, 1.f }));
		gameWinText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
		window.draw(gameWinText);
		
		scoreTotalText.setOrigin(GetTextOrigin(scoreTotalText, { 0.5f, 1.f }));
		scoreTotalText.setPosition(viewSize.x / 2.f, viewSize.y / 2 + 200.f);
		window.draw(scoreTotalText);
		
		std::vector<sf::Text*> textsList;
		textsList.reserve(recordsTableTexts.size());
		for (auto& text : recordsTableTexts)
		{
			textsList.push_back(&text);
		}

		sf::Vector2f tablePosition = { viewSize.x / 2, viewSize.y / 2.f };
		DrawTextList(window, textsList, 10.f, Orientation::Vertical, Alignment::Min, tablePosition, { 0.5f, 0.f });

		hintText.setOrigin(GetTextOrigin(hintText, { 0.5f, 1.f }));
		hintText.setPosition(viewSize.x / 2.f, viewSize.y - 50.f);
		window.draw(hintText);
		menu.Draw(window, hintText.getPosition(), {0.5f, 0.f});
	}
}
