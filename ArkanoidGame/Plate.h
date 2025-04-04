#pragma once
#include <SFML/Graphics.hpp>
#include "GameSettings.h"
#include "Object.h"
#include <array>
#include "Colladiable.h"


namespace Rogalique
{
	class Ball;

	class Plate : public Object, public Colladiable
	{
	public:
		Plate(const sf::Vector2f& position);
		~Plate() =default;
		void Update(float timeDelta)override;
		bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
		bool CheckCollision(std::shared_ptr<Colladiable> collidable) override;
		void SetLonger(bool longer);
	private:
		float YPosition = SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATE_HEIGHT / 2;
		void OnHit() override;
		bool longer = false;
		float preLongerWidth;
		float preLongerHeight;
	};
}
