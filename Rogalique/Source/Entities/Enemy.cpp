#include "Enemy.h"

#include "CreeperExplosion.h"
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
    auto renderer =
        gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
    renderer->SetTexture(
        *EngineCore::ResourceSystem::Instance()->GetTextureShared("cacodemon"));
    renderer->SetPixelSize(100, 100);

    auto direction = gameObject->AddComponent<DirectionComponent>();
    
    gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    gameObject->AddComponent<EngineCore::RigidbodyComponent>();
    
    auto healthComponent = gameObject->AddComponent<HealthComponent>();
    healthComponent->SetHealth(health);
    
    auto fighter = gameObject->AddComponent<FightComponent>();
    fighter->SetDamage(damage);
    fighter->SetTargetType(target);
}

Creeper::Creeper(const EngineCore::Vector2Df& position,
                 const TargetType& target, int damage, int health,
                 float speed) {
    gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("enemy");

    auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    transform->SetWorldPosition(position);
    auto enemyAi = gameObject->AddComponent<EnemyAIComponent>();
    enemyAi->SetMoveSpeed(speed);
    auto move = gameObject->AddComponent<EngineCore::MoveComponent>();
    
    auto renderer =
        gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
    renderer->SetTexture(*EngineCore::ResourceSystem::Instance()->GetTextureMapElementShared("enemyTM", 0));
    renderer->SetPixelSize(100, 100);

    auto direction = gameObject->AddComponent<DirectionComponent>();
    
    auto collider =
        gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    
    auto animator = gameObject->AddComponent<EngineCore::SpriteMovementAnimationComponent>();
    animator->Initialize("enemyTM", 6.f);
    
    gameObject->AddComponent<EngineCore::RigidbodyComponent>();
    
    auto creaperExplosion = gameObject->AddComponent<CreeperExplosion>();

    auto healthComponent = gameObject->AddComponent<HealthComponent>();
    healthComponent->SetHealth(health);

    auto fighter = gameObject->AddComponent<FightComponent>();
    fighter->SetDamage(damage);
    fighter->SetTargetType(target);
}

}  // namespace Rogalique