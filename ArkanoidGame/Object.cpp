#include "Object.h"
#include "Sprite.h"
#include <assert.h>
#include "SFML/Graphics.hpp"

namespace Rogalique {
	Object::Object(const std::string& texturePath, const sf::Vector2f& position, float width, float height) :
		startPosition(position)
	{
		if (!texturePath.empty()) {
			assert(texture.loadFromFile(texturePath));
		}
		InitSprite(sprite,width,height,texture);
		sprite.setPosition(position);
	}

	void Object::Draw(sf::RenderWindow& window)
	{
		DrawSprite(sprite, window);
	}

	void Object::restart()
	{
		sprite.setPosition(startPosition);
	}
}
