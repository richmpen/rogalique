#pragma once
#include <memory>
#include "SFML/Graphics.hpp"

namespace Arkanoid
{
	class Bonus;

	class BonusFactory
	{
	public:

		virtual std::shared_ptr<Bonus> CreateBonus(const sf::Vector2f& position) = 0;
		virtual ~BonusFactory() = default;
	};
    
    class FireBallBonusFactory final: public BonusFactory
    {
    public:
        std::shared_ptr<Bonus> CreateBonus(const sf::Vector2f& position) override;
        ~FireBallBonusFactory() = default;
    };

    class GlassBlocksBonusFactory final : public BonusFactory
    {
    public:
        std::shared_ptr<Bonus> CreateBonus(const sf::Vector2f& position) override;
        ~GlassBlocksBonusFactory() = default;
    };

    class LongerPlateBonusFactory final : public BonusFactory
    {
    public:
        std::shared_ptr<Bonus> CreateBonus(const sf::Vector2f& position) override;
        ~LongerPlateBonusFactory() = default;
    };
}