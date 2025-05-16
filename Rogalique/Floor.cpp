#include "Floor.h"
#include "ResourceSystem.h"
#include "SpriteRendererComponent.h"

namespace Rogalique
{
    Floor::Floor(const EngineCore::Vector2Df& position)
    {
        gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("Floor");

        auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
        transform->SetWorldPosition(position);

        auto renderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();

        renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared("floor"));
        renderer->SetPixelSize(100, 100);
        
    }
    EngineCore::GameObject* Floor::GetGameObject()
    {
        return gameObject;
    }
    
}
