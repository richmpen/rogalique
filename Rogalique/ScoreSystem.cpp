#include "ScoreSystem.h"
#include "Block.h"
#include "IObserver.h"
#include <fstream>
#include "GameSettings.h"

namespace Rogalique
{
	void ScoreSystem::SetScore(const int score)
	{this->score = score;}

	
	void ScoreSystem::SetTotalScore(int currentScore)
	{
		std::ofstream file(SETTINGS.SCORE_CONFIG_PATH, std::ios::app);
		currentScore += GetTotalScore();
		if (file.is_open())
		{
			file << currentScore << std::endl;
		}
		file.close();
	}

	int ScoreSystem::GetTotalScore()
	{
		std::ifstream file(SETTINGS.SCORE_CONFIG_PATH);
		if (!file.is_open())
		{
			return 0;
		}

		int totalScore = 0;
		int currentScore;
		
		while (file >> currentScore)
		{
			totalScore = currentScore;
		}

		file.close();
		
		return totalScore;
	}

}
