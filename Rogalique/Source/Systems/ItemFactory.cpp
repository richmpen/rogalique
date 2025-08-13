#include "ItemFactory.h"

#include "InventorySystem.h"

namespace Rogalique {

std::shared_ptr<Item> HealthItemFactory::CreateItem(
    ItemType type, int count, const EngineCore::Vector2Df& position,
    const std::string& textureName) {
    auto item =
        std::make_shared<HealthItem>(type, count, position, textureName);
    InventorySystem::Instance()->ItemCollision(item);
    return item;
}

std::shared_ptr<Item> ArmorItemFactory::CreateItem(
    ItemType type, int count, const EngineCore::Vector2Df& position,
    const std::string& textureName) {
    auto item = std::make_shared<ArmorItem>(type, count, position, textureName);
    InventorySystem::Instance()->ItemCollision(item);
    return item;
}

std::shared_ptr<Item> AmmoItemFactory::CreateItem(
    ItemType type, int count, const EngineCore::Vector2Df& position,
    const std::string& textureName) {
    auto item = std::make_shared<AmmoItem>(type, count, position, textureName);
    InventorySystem::Instance()->ItemCollision(item);
    return item;
}

std::shared_ptr<Item> WeaponItemFactory::CreateItem(
    ItemType type, int count, const EngineCore::Vector2Df& position,
    const std::string& textureName) {
    auto item =
        std::make_shared<WeaponItem>(type, count, position, textureName);
    InventorySystem::Instance()->ItemCollision(item);
    return item;
}
}  // namespace Rogalique
