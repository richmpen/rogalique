#include "Enemy.h"
#include <ResourceSystem.h>


namespace Rogalique
{
    Enemy::Enemy(const EngineCore::Vector2Df& position)
    {
        gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("Enemy");

        auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
        transform->SetWorldPosition(position);
        transform->Print();

        auto renderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();

        renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared("enemy"));
        renderer->SetPixelSize(100, 100);

        auto input = gameObject->AddComponent<EngineCore::InputComponent>();

        // auto move = gameObject->AddComponent<EngineCore::MoveComponent>();
        // move->SetSpeed(200.f);

        // auto spriteDirection = gameObject->AddComponent<EngineCore::DirectionComponent>();

        auto collider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();

        auto rigidbody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();
        //Experemental
        /*auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
        transform->RotateBy(90.f);
        transform->MoveBy({ 1.f, 0.f });

        auto test = EngineCore::GameWorld::Instance()->CreateGameObject();
        auto testTransform = test->GetComponent<EngineCore::TransformComponent>();
        testTransform->SetParent(transform);

        transform->RotateBy(-90.f);
        transform->Print();
        testTransform->Print();*/
    }

    EngineCore::GameObject* Enemy::GetGameObject()
    {
        return gameObject;
    }
}