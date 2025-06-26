
#include "DirectionComponent.h"
#include "Player.h"
#include "EnemyAIComponent.h"
#include "GameWorld.h"

namespace Rogalique {

DirectionComponent::DirectionComponent(EngineCore::GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<EngineCore::InputComponent>();
    spriteRenderer =
        gameObject->GetComponent<EngineCore::SpriteRendererComponent>();
    transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    enemyAI = gameObject->GetComponent<EnemyAIComponent>();
    playerObject =
        EngineCore::GameWorld::Instance()->FindGameObjectByName("Player");
    
}

void DirectionComponent::Update(float deltaTime) {
    auto playerPos = playerObject->GetComponent<EngineCore::TransformComponent>()->GetWorldPosition(); 
    auto GameObjectPosition = gameObject->GetComponent<EngineCore::TransformComponent>()->GetWorldPosition();
    
    if (gameObject->GetComponent<EngineCore::InputComponent>() != 0) {
        if (input->GetHorizontalAxis() < 0) {
            spriteRenderer->FlipX(true);
            // LOG_INFO(gameObject->GetName() << ": sprite flip Right");
        } else if (input->GetHorizontalAxis() > 0) {
            spriteRenderer->FlipX(false);
            // LOG_INFO(gameObject->GetName() << ": sprite flip Left");
        }
    }
    if (gameObject->GetComponent<EnemyAIComponent>() != 0 && enemyAI->GetIsDiscovered() == true) {
        if (playerPos.x >= GameObjectPosition.x) {
            spriteRenderer->FlipX(false);
        }else {
            spriteRenderer->FlipX(true);
        }
    }
    
}

void DirectionComponent::Render() {}
}  // namespace Rogalique
