#pragma once
#include <iostream>


namespace Arkanoid
{
	class ScoreSystem
	{
	public:
		static ScoreSystem& Instance() {
			static ScoreSystem instance;
			return instance;
		}
		void SetScore(const int score);
		int GetScore() const { return score;}
		
		void SetTotalScore(int currentScore);
		int GetTotalScore();
		
	private:
		ScoreSystem() = default;
		int score = 0;
	};

}

