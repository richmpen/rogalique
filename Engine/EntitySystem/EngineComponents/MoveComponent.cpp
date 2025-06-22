#include "pch.h"

#include "MoveComponent.h"

namespace EngineCore {
MoveComponent::MoveComponent(GameObject* gameObject) : Component(gameObject) {
    input = gameObject->GetComponent<InputComponent>();
    transform = gameObject->GetComponent<TransformComponent>();
    if (input == nullptr) {
        LOG_ERROR("MoveComponent required to InputComponent.");
        gameObject->RemoveComponent(this);
        return;
    }
    if (transform == nullptr) {
        LOG_ERROR("MoveComponent required to TransformComponent.");
        gameObject->RemoveComponent(this);
        return;
    }
}

void MoveComponent::Update(float deltaTime) {
    transform->MoveBy(
        speed * deltaTime *
        Vector2Df{input->GetHorizontalAxis(), input->GetVerticalAxis()});
}

void MoveComponent::Render() {}
}  // namespace EngineCore
