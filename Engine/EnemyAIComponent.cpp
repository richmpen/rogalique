#include "pch.h"

#include "EnemyAIComponent.h"

#include "GameWorld.h"
#include "TransformComponent.h"

namespace EngineCore {

EnemyAIComponent::EnemyAIComponent(GameObject* gameObject)
    : Component(gameObject), playerObject(nullptr) {
    chaseDistance = 400.0f;
    playerObject = GameWorld::Instance()->FindGameObjectByName("Player");
}

void EnemyAIComponent::Update(float deltaTime) {
    TransformComponent* enemyTransform =
        GetGameObject()->GetComponent<TransformComponent>();
    TransformComponent* objectTransform =
        playerObject->GetComponent<TransformComponent>();

    if (enemyTransform && objectTransform) {
        Vector2Df enemyPos = enemyTransform->GetWorldPosition();
        Vector2Df objectPos = objectTransform->GetWorldPosition();
        Vector2Df directionToObject = objectPos - enemyPos;

        float distanceSquared = directionToObject.x * directionToObject.x +
                                directionToObject.y * directionToObject.y;

        if (distanceSquared <= chaseDistance * chaseDistance) {
            LOG_INFO("Enemy begins the pursuit to " << playerObject->GetName());
            float distance = sqrt(distanceSquared);
            if (distance > 0) {
                directionToObject.x /= distance;
                directionToObject.y /= distance;
            }

            Vector2Df movement = directionToObject * speed * deltaTime;
            enemyTransform->MoveBy(movement);
        }
    }
}

void EnemyAIComponent::Render() {}

}  // namespace EngineCore