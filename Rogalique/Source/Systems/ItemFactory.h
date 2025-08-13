#pragma once
#include "Item.h"
#include "Logger.h"

namespace Rogalique {

class ItemFactory {
   public:
    virtual std::shared_ptr<Item> CreateItem(
        ItemType type, int count, const EngineCore::Vector2Df& position,
        const std::string& textureName) = 0;
};

class HealthItemFactory final : public ItemFactory {
   public:
    std::shared_ptr<Item> CreateItem(ItemType type, int count,
                                     const EngineCore::Vector2Df& position,
                                     const std::string& textureName) override;
    ~HealthItemFactory() = default;
};

class ArmorItemFactory final : public ItemFactory {
   public:
    std::shared_ptr<Item> CreateItem(ItemType type, int count,
                                     const EngineCore::Vector2Df& position,
                                     const std::string& textureName) override;
    ~ArmorItemFactory() = default;
};

class AmmoItemFactory final : public ItemFactory {
   public:
    std::shared_ptr<Item> CreateItem(ItemType type, int count,
                                     const EngineCore::Vector2Df& position,
                                     const std::string& textureName) override;
    ~AmmoItemFactory() = default;
};

class WeaponItemFactory final : public ItemFactory {
   public:
    std::shared_ptr<Item> CreateItem(ItemType type, int count,
                                     const EngineCore::Vector2Df& position,
                                     const std::string& textureName) override;
    ~WeaponItemFactory() = default;
};

}  // namespace Rogalique
