#include "Player.h"

#include "DirectionComponent.h"
#include "GameSettings.h"
#include "HealthComponent.h"

#include <MoveComponent.h>
#include <ResourceSystem.h>
#include <SpriteColliderComponent.h>
#include <SpriteMovementAnimationComponent.h>

namespace Rogalique {
Player::Player(const EngineCore::Vector2Df& position, const TargetType& target,
               int damage, int health) {
    gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("Player");
    auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    transform->SetWorldPosition(position);

    auto renderer =
        gameObject->AddComponent<EngineCore::SpriteRendererComponent>();

    renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureMapElementShared("playerTMALL", 0));
    renderer->SetPixelSize(100, 100);

    auto camera = gameObject->AddComponent<EngineCore::CameraComponent>();
    camera->SetWindow(&EngineCore::RenderSystem::Instance()->GetMainWindow());
    camera->SetBaseResolution(SETTINGS.PLAYER_CAMERA_WIDTH,
                              SETTINGS.PLAYER_CAMERA_HEIGHT);

    auto input = gameObject->AddComponent<EngineCore::InputComponent>();

    auto move = gameObject->AddComponent<EngineCore::MoveComponent>();
    move->SetSpeed(SETTINGS.PLAYER_SPEED);
    
    auto animation = gameObject->AddComponent<EngineCore::SpriteMovementAnimationComponent>();
    animation->Initialize("playerTMALL", 10.f);

    auto direction = gameObject->AddComponent<DirectionComponent>();
    direction->AddDirectionMoveAnimation(directionEnum::Left, 4, 7, true);
    direction->AddDirectionMoveAnimation(directionEnum::Right, 4, 7, false);
    direction->AddDirectionMoveAnimation(directionEnum::Up, 13, 15, false);
    direction->AddDirectionMoveAnimation(directionEnum::Down, 18, 19, false);
    auto collider =
        gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    

    auto rigidbody = gameObject->AddComponent<EngineCore::RigidbodyComponent>();

    auto healthComponent = gameObject->AddComponent<HealthComponent>();
    healthComponent->SetHealth(health);

    auto fighter = gameObject->AddComponent<FightComponent>();

    fighter->SetDamage(damage);
    fighter->SetTargetType(target);

    // Experemental
    /*auto transform =
    gameObject->GetComponent<EngineCore::TransformComponent>();
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

EngineCore::GameObject* Player::GetGameObject() { return gameObject; }
}  // namespace Rogalique
