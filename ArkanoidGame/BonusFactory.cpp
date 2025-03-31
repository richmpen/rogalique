#include "BonusFactory.h"
#include "Bonus.h"

namespace Arkanoid
{
    std::shared_ptr<Bonus> FireBallBonusFactory::CreateBonus(const sf::Vector2f& position) {
        return std::make_shared<FireBall>("FireBallBonus.png", position);
    }

    std::shared_ptr<Bonus> GlassBlocksBonusFactory::CreateBonus(const sf::Vector2f& position)
    {
        return std::make_shared<GlassBlocks>("GlassBlocksBonus.png", position);
    }

    std::shared_ptr<Bonus> LongerPlateBonusFactory::CreateBonus(const sf::Vector2f& position)
    {
        return std::make_shared<LongerPlate>("LongPlateBonus.png", position);
    }
}