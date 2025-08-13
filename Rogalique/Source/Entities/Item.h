#pragma once
#include "GameObject.h"
#include "ItemType.h"
#include "SpriteColliderComponent.h"

#include "SFML/Graphics/Texture.hpp"

namespace Rogalique {

class Item {
   public:
    Item() = default;
    Item(ItemType itemType, int itemCount, EngineCore::Vector2Df itemPosition,
         const std::string& textureNameParam);
    virtual ~Item() = default;

    virtual ItemType GetType() const { return type; }
    virtual int GetCount() const { return count; }
    virtual void AddCount(int addCount) { count += addCount; }
    virtual std::string GetTextureName() const { return textureName; }
    virtual bool Use(EngineCore::GameObject* gameObject) = 0;
    virtual void HideInWorld();

    virtual EngineCore::GameObject* GetGameObject();

   protected:
    ItemType type;
    int count;
    EngineCore::Vector2Df position;
    std::string textureName;
    bool isPickUp;
    EngineCore::GameObject* gameObject;
};

class HealthItem : public Item {
   public:
    HealthItem(ItemType type, int count, EngineCore::Vector2Df position,
               const std::string& textureName);
    ~HealthItem() {}
    bool Use(EngineCore::GameObject* gameObject) override;
};

class ArmorItem : public Item {
   public:
    ArmorItem(ItemType type, int count, EngineCore::Vector2Df position,
              const std::string& textureName);
    ~ArmorItem() {}
    bool Use(EngineCore::GameObject* gameObject) override;
};

class AmmoItem : public Item {
   public:
    AmmoItem(ItemType type, int count, EngineCore::Vector2Df position,
             const std::string& textureName);
    ~AmmoItem() {}
    bool Use(EngineCore::GameObject* gameObject) override;
};

class WeaponItem : public Item {
   public:
    WeaponItem(ItemType type, int count, EngineCore::Vector2Df position,
               const std::string& textureName);
    ~WeaponItem() {}
    bool Use(EngineCore::GameObject* gameObject) override;
};

}  // namespace Rogalique
