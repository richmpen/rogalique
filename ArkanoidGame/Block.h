#pragma once
#include <queue>
#include "Colladiable.h"
#include "Object.h"
#include "IDelayedAction.h"
#include "IObserver.h"

namespace Arkanoid {
	class Ball;
	class Block : public Object, public Colladiable, public IObservable
	{
	protected:	
		void OnHit() override;
		int hitcount = 1;
		sf::Texture texture;
	public:
		int originalHitcount = 1;
		Block(const std::string& texturePath,sf::Vector2f position);
		virtual ~Block();
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<Colladiable> collidableObject) const override;
		bool isDestroyed();
		virtual int GetScoreValue() const { return 0; };
		void SetFragile(bool fragile);
		void SetHitcount(int value) { hitcount = value; }
		int GetHitcount() const { return hitcount; }
	};

	class SmoothDestroyableBlock : public Block, public IDelayedAction
	{
		protected:
		void OnHit() override;
		public:
		SmoothDestroyableBlock(const std::string& texturePath, sf::Vector2f position, sf::Color color);
		~SmoothDestroyableBlock() = default;
		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
		bool isDestroyed();
		void FinalAction() override;
		void EachTickAction(float timeDelta) override;
		int GetScoreValue() const override;
		private:
		sf::Color color = sf::Color::White;
		bool GlassBlock = false;
	};

	class UnbreackableBlock : public Block
	{
	protected:
		void OnHit() override;
		public:
		UnbreackableBlock(const std::string& texturePath, const sf::Vector2f& position);
		int GetScoreValue() const override;
		bool isDestroyed();
	};

	class ThreeHitBlock : public Block
	{
		protected:
		void OnHit() override;
		public:
		
		ThreeHitBlock(const std::string& texturePath, const sf::Vector2f& position);
		~ThreeHitBlock() = default;
		bool GetCollision(std::shared_ptr<Colladiable> collidableObject) const override;
		int GetScoreValue() const override;
		void SwitchBlockTexture();
		bool isDestroyed();

		private:
		std::queue<sf::Texture> DestroyTextures;
		sf::Texture brokenTexture;
		sf::Texture lastBrokenTexture;
	};

	
}