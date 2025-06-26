#include "pch.h"

#include "MoveComponent.h"

#include "GameWorld.h"

namespace EngineCore {
MoveComponent::MoveComponent(GameObject* gameObject) : Component(gameObject) {
    input = gameObject->GetComponent<InputComponent>(); 
    transform = gameObject->GetComponent<TransformComponent>();
    
    if (transform == nullptr) {
        LOG_ERROR("MoveComponent required to TransformComponent.");
        gameObject->RemoveComponent(this);
        return;
    }
}

float MoveComponent::GetAccelerationSquared() const {
    return acceleration.x * acceleration.x + acceleration.y * acceleration.y;
}

void MoveComponent::Update(float deltaTime) {
    if (gameObject->GetComponent<InputComponent>() != 0) {
        transform->MoveBy(
            speed * deltaTime *
            Vector2Df{input->GetHorizontalAxis(), input->GetVerticalAxis()});
    }

    acceleration = transform->GetWorldPosition() - previousPosition;
    previousPosition = transform->GetWorldPosition();
}

void MoveComponent::Render() {}
}  // namespace EngineCore
