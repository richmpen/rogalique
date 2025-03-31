#pragma once
#include "IDelayedAction.h"
#include "Bonus.h"
#include "Plate.h"
#include "Ball.h"
#include "Block.h"

namespace Arkanoid {

    class BonusEffect : public IDelayedAction {
    public:
        BonusEffect(float duration, 
                    std::shared_ptr<Bonus> bonus,
                    std::shared_ptr<Plate> plate,
                    std::shared_ptr<Ball> ball, 
                    const std::vector<std::shared_ptr<Block>>& blocks)
            : bonusPtr_(bonus)
            , plate_(plate)
            , ball_(ball)
            , blocks_(blocks)
        {
            StartTimer(duration);
            bonusType_ = bonusPtr_->GetType();
            bonusPtr_->BonusApply(plate_, ball_, blocks_);
        }

        void Update(float timeDelta) {
            UpdateTimer(timeDelta);
        }

        void FinalAction() override {
            if (bonusPtr_) {
                bonusPtr_->FinalAction();
            }
        }

        void EachTickAction(float timeDelta) override {
        }

        BonusType GetBonusType() const {
            return bonusType_;
        }

        void ResetTimer(float duration) {
            currentTime_ = duration;
            destroyTime_ = duration;
            isTimerStarted_ = true;
        }

    private:
        std::shared_ptr<Bonus> bonusPtr_;
        std::shared_ptr<Plate> plate_;
        std::shared_ptr<Ball> ball_;
        std::vector<std::shared_ptr<Block>> blocks_;
        BonusType bonusType_;
    };
}