#include "Enemy.h"

#include "EnemyAIComponent.h"
#include "FightComponent.h"
#include "GameObject.h"
#include "GameWorld.h"
#include "ResourceSystem.h"

namespace Rogalique {

EngineCore::GameObject* Enemy::GetGameObject() { return gameObject; }

Cacodemon::Cacodemon(const EngineCore::Vector2Df& position,
                     const EngineCore::TargetType& target, int damage,
                     int health, float speed) {
    gameObject =
        EngineCore::GameWorld::Instance()->CreateGameObject("Cacodemon");

    auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    transform->SetWorldPosition(position);

    auto enemyAi = gameObject->AddComponent<EngineCore::EnemyAIComponent>();
    enemyAi->SetMoveSpeed(speed);
    auto renderer =
        gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
    renderer->SetTexture(
        *EngineCore::ResourceSystem::Instance()->GetTextureShared("cacodemon"));
    renderer->SetPixelSize(100, 100);

    gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    gameObject->AddComponent<EngineCore::RigidbodyComponent>();

    auto fighter = gameObject->AddComponent<EngineCore::FightComponent>();
    fighter->SetDamage(damage);
    fighter->SetHealth(health);
    fighter->SetTargetType(target);
}

Creeper::Creeper(const EngineCore::Vector2Df& position,
                 const EngineCore::TargetType& target, int damage, int health,
                 float speed) {
    gameObject = EngineCore::GameWorld::Instance()->CreateGameObject("Creeper");

    auto transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    transform->SetWorldPosition(position);
    auto enemyAi = gameObject->AddComponent<EngineCore::EnemyAIComponent>();
    enemyAi->SetMoveSpeed(speed);
    auto renderer =
        gameObject->AddComponent<EngineCore::SpriteRendererComponent>();
    renderer->SetTexture(
        *EngineCore::ResourceSystem::Instance()->GetTextureShared("creeper"));
    renderer->SetPixelSize(100, 100);

    gameObject->AddComponent<EngineCore::SpriteColliderComponent>();
    gameObject->AddComponent<EngineCore::RigidbodyComponent>();

    auto fighter = gameObject->AddComponent<EngineCore::FightComponent>();

    fighter->SetDamage(damage);
    fighter->SetHealth(health);
    fighter->SetTargetType(target);
}

}  // namespace Rogalique