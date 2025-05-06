#include "Player.h"
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <MoveComponent.h>
#include <DirectionComponent.h>


namespace Rogalique
{
    Player::Player(const EngineCore::Vector2Df& position)
    {
        gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("Player");

        auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
        transform->SetWorldPosition(position);
        transform->Print();

        auto renderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();

        renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared("player"));
        renderer->SetPixelSize(100, 100);

        auto camera = gameObject->AddComponent<EngineCore::CameraComponent>();
        camera->SetWindow(&EngineCore::RenderSystem::Instance()->GetMainWindow());
        camera->SetBaseResolution(1280, 720);

        auto input = gameObject->AddComponent<EngineCore::InputComponent>();

        auto move = gameObject->AddComponent<EngineCore::MoveComponent>();
        move->SetSpeed(400.f);

        auto spriteDirection = gameObject->AddComponent<EngineCore::DirectionComponent>();

        auto collider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();

        auto rigidbody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();
        


        

        //Experemental
        /*auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
        transform->RotateBy(90.f);
        transform->MoveBy({ 1.f, 0.f });
        transform->Print();*/

       /* auto test = EngineCore::GameWorld::Instance()->CreateGameObject();
        auto testTransform = test->GetComponent<EngineCore::TransformComponent>();
        testTransform->SetParent(transform);

        transform->RotateBy(-90.f);
        transform->Print();
        testTransform->Print();*/
    }

    EngineCore::GameObject* Player::GetGameObject()
    {
        return gameObject;
    }
}
