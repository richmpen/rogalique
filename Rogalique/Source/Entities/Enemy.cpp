#include "Enemy.h"

#include "DeathAnimation.h"
#include "DirectionComponent.h"
#include "EnemyAIComponent.h"
#include "FightComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "HealthComponent.h"
#include "ResourceSystem.h"
#include "SpriteMovementAnimationComponent.h"

namespace Rogalique {

EngineCore::GameObject* Enemy::GetGameObject() { return gameObject; }

Cacodemon::Cacodemon(const EngineCore::Vector2Df& position,
                     const TargetType& target, int damage, int health,
                     float speed) {
    gameObject =
        EngineCore::GameWorld::Instance()->CreateGameObject("Cacodemon");

    auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    transform->SetWorldPosition(position);

    auto enemyAi = gameObject->AddComponent<EnemyAIComponent>();
    enemyAi->SetMoveSpeed(speed);
    auto move = gameObject->AddComponent<EngineCore::MoveComponent>();
    auto renderer =
        gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
    renderer->SetTexture(
        *EngineCore::ResourceSystem::Instance()->GetTextureMapElementShared(
            "cacodemonTM", 0));
    renderer->SetPixelSize(100, 100);

    auto moveAnimator =
        gameObject
            ->AddComponent<EngineCore::SpriteMovementAnimationComponent>();
    moveAnimator->Initialize("cacodemonTM", 10.f);
    
    auto direction = gameObject->AddComponent<DirectionComponent>();
    direction->AddDirectionMoveAnimation(directionEnum::Right, 0, 2, true);
    direction->AddDirectionMoveAnimation(directionEnum::Left, 0, 2, false);

    gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    gameObject->AddComponent<EngineCore::RigidbodyComponent>();

    auto healthComponent = gameObject->AddComponent<HealthComponent>();
    healthComponent->SetHealth(health);

    auto fighter = gameObject->AddComponent<FightComponent>();
    fighter->SetDamage(damage);
    fighter->SetTargetType(target);
}

Demon::Demon(const EngineCore::Vector2Df& position,
                 const TargetType& target, int damage, int health,
                 float speed) {
    gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("Demon");

    auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    transform->SetWorldPosition(position);
    auto enemyAi = gameObject->AddComponent<EnemyAIComponent>();
    enemyAi->SetMoveSpeed(speed);
    auto move = gameObject->AddComponent<EngineCore::MoveComponent>();

    auto renderer =
        gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
    renderer->SetTexture(
        *EngineCore::ResourceSystem::Instance()->GetTextureMapElementShared(
            "demonWalk", 0));
    renderer->SetPixelSize(100, 100);

    auto moveAnimator =
        gameObject
            ->AddComponent<EngineCore::SpriteMovementAnimationComponent>();
    moveAnimator->Initialize("demonWalk", 6.f);

    auto direction = gameObject->AddComponent<DirectionComponent>();
    direction->AddDirectionMoveAnimation(directionEnum::Right, 0, 2, false);
    direction->AddDirectionMoveAnimation(directionEnum::Left, 0, 2, true);
    
    gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    gameObject->AddComponent<EngineCore::RigidbodyComponent>();

    auto creaperExplosion = gameObject->AddComponent<DeathAnimation>();

    auto healthComponent = gameObject->AddComponent<HealthComponent>();
    healthComponent->SetHealth(health);

    auto fighter = gameObject->AddComponent<FightComponent>();
    fighter->SetDamage(damage);
    fighter->SetTargetType(target);
}

}  // namespace Rogalique