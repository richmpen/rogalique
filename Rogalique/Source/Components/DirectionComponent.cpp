
#include "DirectionComponent.h"

#include "EnemyAIComponent.h"
#include "GameWorld.h"
#include "Player.h"

namespace Rogalique {

DirectionComponent::DirectionComponent(EngineCore::GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<EngineCore::InputComponent>();
    spriteRenderer =
        gameObject->GetComponent<EngineCore::SpriteRendererComponent>();
    transform = gameObject->GetComponent<EngineCore::TransformComponent>();
    enemyAI = gameObject->GetComponent<EnemyAIComponent>();
    playerObject = EngineCore::GameWorld::Instance()->FindPlayer();
    moveAnimation =
        gameObject
            ->GetComponent<EngineCore::SpriteMovementAnimationComponent>();
}

void DirectionComponent::SwitchDirection(directionEnum dir) { direction = dir; }

directionEnum DirectionComponent::GetCurrentDirection() const {
    return direction;
}

void DirectionComponent::AddDirectionMoveAnimation(directionEnum dir,
                                                   int firstFrame,
                                                   int lastFrame, bool FlipX) {
    animationMap[dir] = {firstFrame, lastFrame, FlipX};
}

void DirectionComponent::Update(float deltaTime) {
    auto playerPos =
        playerObject->GetComponent<EngineCore::TransformComponent>()
            ->GetWorldPosition();
    auto GameObjectPosition = transform->GetWorldPosition();
    directionEnum newDirection = direction;

    // Player logic
    if (input && moveAnimation) {
        if (input->GetHorizontalAxis() < 0) {
            newDirection = directionEnum::Left;
        } else if (input->GetHorizontalAxis() > 0) {
            newDirection = directionEnum::Right;
        } else if (input->GetVerticalAxis() < 0) {
            newDirection = directionEnum::Down;
        } else if (input->GetVerticalAxis() > 0) {
            newDirection = directionEnum::Up;
        }

        if (newDirection != direction) {
            auto it = animationMap.find(newDirection);
            if (it != animationMap.end()) {
                moveAnimation->PlayAnimation(it->second.startFrame,
                                             it->second.endFrame);
                spriteRenderer->FlipX(it->second.flipX);
                SwitchDirection(newDirection);
            }
        }
    }

    // Enemy logic
    if (enemyAI && enemyAI->GetIsDiscovered()) {
        newDirection = (playerPos.x >= GameObjectPosition.x)
                           ? directionEnum::Left
                           : directionEnum::Right;
        if (newDirection != direction) {
            auto it = animationMap.find(newDirection);
            if (it != animationMap.end()) {
                moveAnimation->PlayAnimation(it->second.startFrame,
                                             it->second.endFrame);
                spriteRenderer->FlipX(it->second.flipX);
                SwitchDirection(newDirection);
            }
        }
    }
}

void DirectionComponent::Render() {}
}  // namespace Rogalique
