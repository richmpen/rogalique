#pragma once
#include <SFML/Graphics.hpp>
#include "Colladiable.h"
#include "Object.h"
#include "IObserver.h"
#include "GameSettings.h"

namespace Rogalique {
	
	class Plate;

	enum class Turn {
		X,
		Y,
		Both
	};

	class Ball : public Object, public Colladiable, public IObservable
	{
	public:
		Ball(const sf::Vector2f& position);
		~Ball() = default;
		void Update(float timeDelta) override;
		void Turning(Turn directions);
		void ChangeAngle(float angle);
		void SetPositionOnPlate(const sf::Vector2f positionPlate);
		bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
		void restart() override;
		void SetFireBall(bool active);
	private:
		void OnHit() override;
		sf::Vector2f dir;
		float lastAngle = 90;
		sf::Texture fireTexture;
		float speed;
	};
}