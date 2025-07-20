#pragma once
#include "GameObject.h"
#include "ItemType.h"
#include "SpriteColliderComponent.h"

#include "SFML/Graphics/Texture.hpp"


namespace Rogalique {

    class Item {
    public:
        Item(ItemType type, int count, sf::Vector2f position, const std::string& textureName);

        ItemType GetType() const { return type; }
        int GetCount() const {return count;}
        void AddCount(int addCount){count += addCount;}
        std::string GetTextureName() const { return textureName; }
        
        virtual EngineCore::GameObject* GetGameObject();
        virtual void Use(EngineCore::GameObject* player);
        
    private:
        ItemType type;
        int count;
        sf::Vector2f position;
        std::string textureName;
        EngineCore::GameObject* gameObject;
        bool isPickUp;
    };
}
