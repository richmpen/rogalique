#pragma once
namespace EngineCore {
	class ColliderComponent;
	class Collision {
	public:
		Collision(ColliderComponent* newFirst, ColliderComponent* newSecond, sf::FloatRect newCollisionRect) : first(newFirst), second(newSecond), collisionRect(newCollisionRect) {

		};
	private:
		ColliderComponent* first;
		ColliderComponent* second;
		sf::FloatRect collisionRect;
	};
}