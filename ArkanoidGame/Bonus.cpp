#include "Bonus.h"
#include "GameSettings.h"
#include <assert.h>
#include "Sprite.h"
#include "Ball.h"
#include "Plate.h"
#include "Block.h"
#include <iostream>
#include <string>


namespace Rogalique {

    Bonus::Bonus(const std::string& texturePath, const sf::Vector2f& position, float width, float height)
        : Object(SETTINGS.TEXTURES_PATH + texturePath, position, width, height) {
        assert(texture.loadFromFile(SETTINGS.TEXTURES_PATH + texturePath));
        texture.setSmooth(true);
        sprite.setTexture(texture);
    }

    void Bonus::Update(float timeDelta) {
        sprite.setPosition(sprite.getPosition().x, sprite.getPosition().y + speed * timeDelta);
        UpdateTimer(timeDelta);
    }

    bool Bonus::GetCollision(std::shared_ptr<Colladiable> collidableObject) const {
        auto object = std::dynamic_pointer_cast<Object>(collidableObject);
        if (!object) return false;
        return GetRect().intersects(object->GetRect());
    }

    void Bonus::FinalAction() {
        isActive = false;
    }

    FireBall::FireBall(const std::string& texturePath, const sf::Vector2f& position)
        : Bonus(texturePath, position, SETTINGS.BONUS_SIZE, SETTINGS.BONUS_SIZE) {
    }

    void FireBall::Update(float timeDelta) {
        Bonus::Update(timeDelta);
    }

    bool FireBall::GetCollision(std::shared_ptr<Colladiable> collidable) const {
        return Bonus::GetCollision(collidable);
    }

    void FireBall::BonusApply(std::shared_ptr<Plate> plate, std::shared_ptr<Ball> ball, std::vector<std::shared_ptr<Block>> blocks) {
        if (ball && !isActive) {
            StartTimer(SETTINGS.BONUS_EFFECT_DELAY);
            isActive = true;
            ptrActiveBall = ball;
            ball->SetFireBall(true);
        }
    }

    void FireBall::FinalAction() {
        isActive = false;
        ptrActiveBall->SetFireBall(false);
    }

    GlassBlocks::GlassBlocks(const std::string& texturePath, const sf::Vector2f& position)
        : Bonus(texturePath, position, SETTINGS.BONUS_SIZE, SETTINGS.BONUS_SIZE) {
    }

    void GlassBlocks::Update(float timeDelta) {
        Bonus::Update(timeDelta);
    }

    bool GlassBlocks::GetCollision(std::shared_ptr<Colladiable> collidable) const {
        return Bonus::GetCollision(collidable);
    }

    void GlassBlocks::BonusApply(std::shared_ptr<Plate> plate, std::shared_ptr<Ball> ball, std::vector<std::shared_ptr<Block>> blocks) {
        if (!isActive) {
            StartTimer(SETTINGS.BONUS_EFFECT_DELAY);
            isActive = true;
            ptrActiveBlocks = blocks;
            for (auto& block : blocks) {
                if (block && block->GetHitcount() != 1) {
                    block->originalHitcount = block->GetHitcount();
                    block->SetHitcount(1);
                }
                else if (block) {
                    block->SetHitcount(1);
                }
            }
        }
    }

    void GlassBlocks::FinalAction() {
        isActive = false;
        for (auto& block : ptrActiveBlocks) {
            if (block) {
                block->SetHitcount(block->originalHitcount);
            }
        }
    }

    LongerPlate::LongerPlate(const std::string& texturePath, const sf::Vector2f& position)
        : Bonus(texturePath, position, SETTINGS.BONUS_SIZE, SETTINGS.BONUS_SIZE) {
    }

    void LongerPlate::Update(float timeDelta) {
        Bonus::Update(timeDelta);
    }

    bool LongerPlate::GetCollision(std::shared_ptr<Colladiable> collidable) const {
        return Bonus::GetCollision(collidable);
    }

    void LongerPlate::BonusApply(std::shared_ptr<Plate> plate, std::shared_ptr<Ball> ball, std::vector<std::shared_ptr<Block>> blocks) {
        if (plate && !isActive) {
            StartTimer(SETTINGS.BONUS_EFFECT_DELAY);
            isActive = true;
            ptrActivePlate = plate;
            plate->SetLonger(true);
        }
    }

    void LongerPlate::FinalAction() {
        isActive = false;
        ptrActivePlate->SetLonger(false);
    }
}