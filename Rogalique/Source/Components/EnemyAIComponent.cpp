
#include "EnemyAIComponent.h"

#include "GameSettings.h"
#include "GameWorld.h"
#include "TransformComponent.h"

namespace Rogalique {

EnemyAIComponent::EnemyAIComponent(EngineCore::GameObject* gameObject)
    : Component(gameObject) {
    chaseDistance = SETTINGS.ENEMY_CHASE_DISTANCE;
    playerObject = EngineCore::GameWorld::Instance()->FindPlayer();
}

void EnemyAIComponent::Update(float deltaTime) {
    EngineCore::TransformComponent* enemyTransform =
        GetGameObject()->GetComponent<EngineCore::TransformComponent>();
    EngineCore::TransformComponent* objectTransform =
        playerObject->GetComponent<EngineCore::TransformComponent>();

    if (enemyTransform && objectTransform) {
        EngineCore::Vector2Df enemyPos = enemyTransform->GetWorldPosition();
        EngineCore::Vector2Df objectPos = objectTransform->GetWorldPosition();
        EngineCore::Vector2Df directionToObject = objectPos - enemyPos;

        float distanceSquared = directionToObject.x * directionToObject.x +
                                directionToObject.y * directionToObject.y;

        if (distanceSquared <= chaseDistance * chaseDistance) {
            LOG_INFO("Enemy begins the pursuit to " << playerObject->GetName());
            discovered = true;
            float distance = sqrt(distanceSquared);
            if (distance > 0) {
                directionToObject.x /= distance;
                directionToObject.y /= distance;
            }
            EngineCore::Vector2Df movement =
                directionToObject * speed * deltaTime;
            enemyTransform->MoveBy(movement);
        } else {
            discovered = false;
        }
    }
}

void EnemyAIComponent::Render() {}

}  // namespace Rogalique