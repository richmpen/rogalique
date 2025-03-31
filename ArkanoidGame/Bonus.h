#pragma once
#include "Object.h"
#include "Colladiable.h"
#include "IDelayedAction.h"
#include "SFML/Graphics.hpp"
#include "Plate.h"
#include "Ball.h"
#include "Block.h"
#include "LevelLoader.h"

namespace Arkanoid {
    class Bonus : public Object, public Colladiable, public IDelayedAction {
    protected:
        sf::Texture texture;
        float speed = SETTINGS.BONUS_SPEED;
        bool isActive = false;
    public:
        void OnHit() override {}
        Bonus(const std::string& texturePath, const sf::Vector2f& position, float width, float height);
        virtual ~Bonus() = default;
        void Update(float timeDelta) override;
        bool GetCollision(std::shared_ptr<Colladiable> collidableObject) const override;
        void Draw(sf::RenderWindow& window) override { Object::Draw(window); }
        sf::Vector2f GetPosition() const { return sprite.getPosition(); }
        virtual void BonusApply(std::shared_ptr<Plate> plate, std::shared_ptr<Ball> ball, std::vector<std::shared_ptr<Block>> blocks) = 0;
        void FinalAction() override;
        void EachTickAction(float timeDelta) override {};
        bool IsActive() const { return isActive; }
        bool IsTimerStarted() const { return isTimerStarted_; }
        virtual BonusType GetType() const = 0;
    };

    class FireBall : public Bonus {
    public:
        void OnHit() override {}
        FireBall(const std::string& texturePath, const sf::Vector2f& position);
        ~FireBall() = default;
        void Update(float timeDelta) override;
        bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
        void BonusApply(std::shared_ptr<Plate> plate, std::shared_ptr<Ball> ball, std::vector<std::shared_ptr<Block>> blocks) override;
        void FinalAction() override;
        void EachTickAction(float timeDelta) override {};
        BonusType GetType() const { return BonusType::FireBall; }
    private:
		std::shared_ptr<Ball> ptrActiveBall;
    };

    class GlassBlocks : public Bonus {
    public:
        void OnHit() override {}
        GlassBlocks(const std::string& texturePath, const sf::Vector2f& position);
        ~GlassBlocks() = default;
        void Update(float timeDelta) override;
        bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
        void BonusApply(std::shared_ptr<Plate> plate, std::shared_ptr<Ball> ball, std::vector<std::shared_ptr<Block>> blocks) override;
        void FinalAction() override;
        void EachTickAction(float timeDelta) override {};
        BonusType GetType() const { return BonusType::GlassBlocks; }
        private:
            std::vector<std::shared_ptr<Block>> ptrActiveBlocks;
    };

    class LongerPlate : public Bonus {
    public:
        void OnHit() override {}
        LongerPlate(const std::string& texturePath, const sf::Vector2f& position);
        ~LongerPlate() = default;
        void Update(float timeDelta) override;
        bool GetCollision(std::shared_ptr<Colladiable> collidable) const override;
        void BonusApply(std::shared_ptr<Plate> plate, std::shared_ptr<Ball> ball, std::vector<std::shared_ptr<Block>> blocks) override;
        void FinalAction() override;
        void EachTickAction(float timeDelta) override {};
        BonusType GetType() const { return BonusType::LongerPlate; }
    private:
        std::shared_ptr<Plate> ptrActivePlate;
    };
}