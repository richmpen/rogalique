#include "Player.h"
#include <ResourceSystem.h>


namespace Rogalique
{
    Player::Player()
    {
        gameObject = EngineCore::GameWorld::Instance()->CreateGameObject();
        auto playerRenderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();

        playerRenderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared("ball"));
        playerRenderer->SetPixelsSize(32, 32);

        auto playerCamera = gameObject->AddComponent<EngineCore::CameraComponent>();
        playerCamera->SetWindow(&EngineCore::RenderSystem::Instance()->GetMainWindow());
        playerCamera->SetBaseResolution(1280, 720);

        auto playerInput = gameObject->AddComponent<EngineCore::InputComponent>();

        auto playerBody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();

        auto playerCollider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();

        

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

    EngineCore::GameObject* Player::GetGameObject()
    {
        return gameObject;
    }
}