#include "Block.h"
#include "Ball.h"
#include "Sprite.h"
#include "Object.h"
#include <algorithm>
#include <iostream>
#include <assert.h>
#include <SFML/Graphics.hpp>

#include "Application.h"

namespace Rogalique {

	Block::Block(const std::string& texturePath, sf::Vector2f position)
		: Object(SETTINGS.TEXTURES_PATH + texturePath, position, SETTINGS.BLOCK_WIDTH, SETTINGS.BLOCK_HEIGHT),
		hitcount(1), originalHitcount(1) {
		assert(texture.loadFromFile(SETTINGS.TEXTURES_PATH + "Block.png"));
		texture.setSmooth(true);
	}

	Block::~Block()
	{
	}
	void Block::OnHit()
	{
		hitcount = 0;
		Emit();
	}

	bool Block::GetCollision(std::shared_ptr<Colladiable> collidableObject) const
	{
		auto object = std::dynamic_pointer_cast<Object>(collidableObject);
		assert(object);
		sf::FloatRect rect = GetRect();
		rect.width *= 1.1;
		return GetRect().intersects(object->GetRect());
	}

	bool Block::isDestroyed()
	{
		return hitcount <= 0;
	}

	void Block::SetFragile(bool fragile) {
		if (fragile) {
			hitcount = 1;
		}
	}

	void Block::Update(float timeDelta)
	{
		
	}

	SmoothDestroyableBlock::SmoothDestroyableBlock(const std::string& texturePath, sf::Vector2f position, sf::Color color)
	: Block("SmoothDestroyableBlock.png", position),
	color(color)
	{
		assert(texture.loadFromFile(SETTINGS.TEXTURES_PATH + "SmoothDestroyableBlock.png"));
		texture.setSmooth(true);
	}

	void SmoothDestroyableBlock::OnHit()
	{
		StartTimer(SETTINGS.BREAK_DELAY);
	}

	void SmoothDestroyableBlock::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}

	bool SmoothDestroyableBlock::GetCollision(std::shared_ptr<Colladiable> collidable) const
	{
		if (isTimerStarted_) {
			return false;
		}
		auto object = std::dynamic_pointer_cast<Object>(collidable);
		sf::FloatRect rect = GetRect();
		rect.width *= 1.1;
		return GetRect().intersects(object->GetRect());
	}

	bool SmoothDestroyableBlock::isDestroyed() 
	{
		return hitcount <= 0 && !isTimerStarted_;
		
	}

	void SmoothDestroyableBlock::FinalAction()
	{
		--hitcount;
		Emit();
	}
	
	void SmoothDestroyableBlock::EachTickAction(float timeDelta)
	{
		color.a = static_cast<sf::Uint8>(255 * (currentTime_ / destroyTime_));
		sprite.setColor(color);
	}

	UnbreackableBlock::UnbreackableBlock(const std::string& texturePath, const sf::Vector2f& position):
	Block("UnbreackableBlock.png", position)
	{
		hitcount = 999;
		assert(texture.loadFromFile(SETTINGS.TEXTURES_PATH + "UnbreackableBlock.png"));
		texture.setSmooth(true);
	}

	void UnbreackableBlock::OnHit()
	{
		--hitcount;
		if (isDestroyed()) { return Emit(); }
	}
	bool UnbreackableBlock::isDestroyed()
	{
		return hitcount <= 0;
	}


	ThreeHitBlock::ThreeHitBlock(const std::string& texturePath, const sf::Vector2f& position):
	Block("CrumblingBlock1.png", position)
	{
		assert(texture.loadFromFile(SETTINGS.TEXTURES_PATH + "CrumblingBlock1.png"));
		assert(brokenTexture.loadFromFile(SETTINGS.TEXTURES_PATH + "CrumblingBlock2.png"));
		assert(lastBrokenTexture.loadFromFile(SETTINGS.TEXTURES_PATH + "CrumblingBlock3.png"));
		DestroyTextures.push(brokenTexture);
		DestroyTextures.push(lastBrokenTexture);
		
		texture.setSmooth(true);
		brokenTexture.setSmooth(true);
		lastBrokenTexture.setSmooth(true);
		
		hitcount = SETTINGS.CRUMBLING_HEALTH;
		originalHitcount = SETTINGS.CRUMBLING_HEALTH;
	}

	void ThreeHitBlock::SwitchBlockTexture()
	{
		if (!DestroyTextures.empty()) {
			texture = DestroyTextures.front();
			sprite.setTexture(texture);
			DestroyTextures.pop();
		}
	}

	bool ThreeHitBlock::isDestroyed()
	{
		return hitcount <= 0;
	}
	
	void ThreeHitBlock::OnHit()
	{
		SwitchBlockTexture();
		--hitcount;
		if (isDestroyed()) {return Emit();}
	}

	bool ThreeHitBlock::GetCollision(std::shared_ptr<Colladiable> collidable) const
	{
		auto object = std::dynamic_pointer_cast<Object>(collidable);
		sf::FloatRect rect = GetRect();
		rect.width *= 1.1;
		return GetRect().intersects(object->GetRect());
	}

	int SmoothDestroyableBlock::GetScoreValue() const {
		return SETTINGS.BALL_SIMPLE_BLOCK_SCORE;
	}
	int UnbreackableBlock::GetScoreValue() const {
		return SETTINGS.BALL_UNBREACKABLE_BLOCK_SCORE;
	}
	int ThreeHitBlock::GetScoreValue() const {
		return SETTINGS.BALL_THREE_HIT_BLOCK_SCORE;
	}
 }
