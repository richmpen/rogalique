#include "Item.h"

#include "CameraComponent.h"
#include "GameWorld.h"
#include "HealthComponent.h"
#include "ImageUI.h"
#include "ItemType.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "InventorySystem.h"

#include <memory>

namespace Rogalique {

Item::Item(ItemType type, int count, sf::Vector2f position, const std::string& textureName) 
    : type(type), count(count), position(position), textureName(textureName) {
    
    if (position != sf::Vector2f(0, 0)) { //need fix
        gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("Item");
        isPickUp = false;
        
        auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
        transform->SetWorldPosition(position.x, position.y);
        
        auto renderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
        renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName));
        renderer->SetPixelSize(100, 100);

        auto collider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
        collider->SetTrigger(false);
        
        auto rigidbody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();
        rigidbody->SetKinematic(true);
        
        InventorySystem* inventory = InventorySystem::Instance();
        inventory->ItemCollision(gameObject, type, count, textureName);
    }
    
}



    EngineCore::GameObject* Item::GetGameObject() {
        return gameObject;
    }

    void Item::Use(EngineCore::GameObject* player) {
    }
}
    

