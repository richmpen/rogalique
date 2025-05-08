#include "Wall.h"
#include "ResourceSystem.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"

namespace Rogalique
{
    Wall::Wall(const EngineCore::Vector2Df& position)
    {
        gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("Wall");

        auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
        transform->SetWorldPosition(position);

        auto renderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
        renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared("wall"));
        renderer->SetPixelSize(100, 100);

        auto collider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
      

        auto rigidbody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();
        rigidbody->SetKinematic(true);
        
        
    }
    EngineCore::GameObject* Wall::GetGameObject()
    {
        return gameObject;
    }

}
