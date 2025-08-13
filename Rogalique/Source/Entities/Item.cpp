#include "Item.h"

#include "CameraComponent.h"
#include "GameWorld.h"
#include "HealthComponent.h"
#include "ArmorComponent.h"
#include "AmmoComponent.h"
#include "ImageUI.h"
#include "ItemType.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"
#include "InventorySystem.h"

#include <memory>

namespace Rogalique {

Item::Item(ItemType itemType, int itemCount, EngineCore::Vector2Df itemPosition, const std::string& textureNameParam) 
    : type(itemType), count(itemCount), position(itemPosition), textureName(textureNameParam), isPickUp(false), gameObject(nullptr) {
}

EngineCore::GameObject* Item::GetGameObject() {
    return gameObject;
}

void Item::HideInWorld() {
    if (gameObject) {
        auto renderer = gameObject->GetComponent<EngineCore::SpriteRendererComponent>();
        if (renderer) {
            gameObject->RemoveComponent(renderer);
        }
        
        auto collider = gameObject->GetComponent<EngineCore::SpriteColliderComponent>();
        if (collider) {
            gameObject->RemoveComponent(collider);
        }
    }
}

HealthItem::HealthItem(ItemType type, int count, const EngineCore::Vector2Df position, const std::string& textureName) 
    : Item(type, count, position, textureName) {
    
    gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("HealthItem");
        
    auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    transform->SetWorldPosition(position.x, position.y);
        
    auto renderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
    renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName));
    renderer->SetPixelSize(100, 100);

    auto collider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    collider->SetTrigger(false);
        
    auto rigidbody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();
    rigidbody->SetKinematic(true);
}

bool HealthItem::Use(EngineCore::GameObject* player) {
    auto healthComponent = player->GetComponent<HealthComponent>();
    
    if (healthComponent && healthComponent->GetHealth() < healthComponent->GetMaxHealth()) {
        healthComponent->AddHealth(50);
        return true;
    }
    else {
        return false;
    }
}

ArmorItem::ArmorItem(ItemType type, int count, const EngineCore::Vector2Df position, const std::string& textureName) 
    : Item(type, count, position, textureName) {
    
    gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("ArmorItem");
        
    auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    transform->SetWorldPosition(position.x, position.y);
        
    auto renderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
    renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName));
    renderer->SetPixelSize(100, 100);

    auto collider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    collider->SetTrigger(false);
        
    auto rigidbody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();
    rigidbody->SetKinematic(true);
}

bool ArmorItem::Use(EngineCore::GameObject* player) {
    auto armorComponent = player->GetComponent<ArmorComponent>();
    
    if (armorComponent && armorComponent->GetArmor() < armorComponent->GetMaxArmor()) {
        armorComponent->AddArmor(50);
        return true;
    }
    else {
        return false;
    }
}

AmmoItem::AmmoItem(ItemType type, int count, const EngineCore::Vector2Df position, const std::string& textureName) 
    : Item(type, count, position, textureName) {
    
    gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("AmmoItem");
        
    auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    transform->SetWorldPosition(position.x, position.y);
        
    auto renderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
    renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName));
    renderer->SetPixelSize(100, 100);

    auto collider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    collider->SetTrigger(false);
        
    auto rigidbody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();
    rigidbody->SetKinematic(true);
}

bool AmmoItem::Use(EngineCore::GameObject* player) {
    auto ammoComponent = player->GetComponent<AmmoComponent>();
    if (ammoComponent) {
        ammoComponent->AddAmmo(50);
    }
    return true;
}

WeaponItem::WeaponItem(ItemType type, int count, const EngineCore::Vector2Df position, const std::string& textureName) 
    : Item(type, count, position, textureName) {
    
    gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("WeaponItem");
        
    auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    transform->SetWorldPosition(position.x, position.y);
        
    auto renderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
    renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared(textureName));
    renderer->SetPixelSize(100, 100);

    auto collider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    collider->SetTrigger(false);
        
    auto rigidbody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();
    rigidbody->SetKinematic(true);
}

bool WeaponItem::Use(EngineCore::GameObject* player) {
    LOG_WARN("Use Weapon Logic: logic not find")
    return false;
}

}
    

