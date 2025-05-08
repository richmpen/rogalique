#include "Enemy.h"
#include "ResourceSystem.h"
#include "EnemyAIComponent.h"
#include "GameObject.h"
#include "GameWorld.h"

namespace Rogalique
{
    Enemy::Enemy(const EngineCore::Vector2Df& position)
    {
        gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("Enemy");

        auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
        transform->SetWorldPosition(position);
        
        gameObject->AddComponent<EngineCore::EnemyAIComponent>();
        
        auto ai = gameObject->AddComponent<EngineCore::EnemyAIComponent>();
        
        auto renderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();

        renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared("enemy"));
        renderer->SetPixelSize(100, 100);
        
        auto collider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();

        auto rigidbody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();
    }

    EngineCore::GameObject* Enemy::GetGameObject()
    {
        return gameObject;
    }
}