#include "GameStateGameOver.h"
#include "Application.h"
#include "Game.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "ScoreSystem.h"

namespace Rogalique
{

	void GameStateGameOver::Init()
	{
		assert(font.loadFromFile(SETTINGS.RESOURCES_PATH + "Fonts/Alata-Regular.ttf"));

		timeSinceGameOver = 0.f;
		sf::Color backgroundColor = sf::Color::Black;
		backgroundColor.a = 200;
		background.setFillColor(backgroundColor);

		gameOverText.setFont(font);
		gameOverText.setCharacterSize(48);
		gameOverText.setStyle(sf::Text::Bold);
		gameOverText.setFillColor(sf::Color::Red);
		gameOverText.setString("GAME OVER");
		
		recordsTableTexts.reserve(SETTINGS.MAX_RECORDS_TABLE_SIZE);

		scoreTotalText.setFont(font);
		scoreTotalText.setCharacterSize(38);
		scoreTotalText.setStyle(sf::Text::Bold);
		scoreTotalText.setFillColor(sf::Color(106, 90, 205, 255));
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
		hintText.setString("Press Space to restart\nEsc to exit to main menu");
	}

	void GameStateGameOver::Shutdown(){}

	void GameStateGameOver::Control(const sf::Event& event)
	{
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Space)
			{
				Application::Instance().GetGame().StartGame();
			}
			else if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().ExitGame();
			}
		}
	}

	void GameStateGameOver::Update(float timeDelta)
	{
		timeSinceGameOver += timeDelta;

		sf::Color gameOverTextColor = (int)timeSinceGameOver % 2 ? sf::Color::Blue : sf::Color::White;
		gameOverText.setFillColor(gameOverTextColor);

	}

	void GameStateGameOver::Draw(sf::RenderWindow& window)
	{
		sf::Vector2f viewSize = window.getView().getSize();

		background.setOrigin(0.f, 0.f);
		background.setSize(viewSize);
		window.draw(background);

		gameOverText.setOrigin(GetTextOrigin(gameOverText, { 0.5f, 1.f }));
		gameOverText.setPosition(viewSize.x / 2.f, viewSize.y / 2 - 50.f);
		window.draw(gameOverText);

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
	}
}
