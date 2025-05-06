#include "Enemy.h"
#include <ResourceSystem.h>
//
//
// namespace Rogalique
// {
//     Enemy::Enemy()
//     {
//         gameObject = EngineCore::GameWorld::Instance()->CreateGameObject();
//         auto EnemyRenderer = gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
//
//         EnemyRenderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureShared("enemy"));
//         EnemyRenderer->SetPixelSize(32, 32);
//
//         auto EnemyCamera = gameObject->AddComponent<EngineCore::CameraComponent>();
//         EnemyCamera->SetWindow(&EngineCore::RenderSystem::Instance()->GetMainWindow());
//         EnemyCamera->SetBaseResolution(1280, 720);
//
//         /*auto EnemyInput = gameObject->AddComponent<EngineCore::InputComponent>();*/
//
//         auto EnemyBody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();
//
//         auto EnemyCollider = gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
//
//
//
//         //Experemental
//         /*auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
//         transform->RotateBy(90.f);
//         transform->MoveBy({ 1.f, 0.f });
//
//         auto test = EngineCore::GameWorld::Instance()->CreateGameObject();
//         auto testTransform = test->GetComponent<EngineCore::TransformComponent>();
//         testTransform->SetParent(transform);
//
//         transform->RotateBy(-90.f);
//         transform->Print();
//         testTransform->Print();*/
//     }
//
//     EngineCore::GameObject* Enemy::GetGameObject()
//     {
//         return gameObject;
//     }
// }