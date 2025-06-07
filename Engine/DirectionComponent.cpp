#include "pch.h"

#include "DirectionComponent.h"

namespace EngineCore {

DirectionComponent::DirectionComponent(GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<InputComponent>();
    spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
}

void DirectionComponent::Update(float deltaTime) {
    if (input->GetHorizontalAxis() < 0) {
        spriteRenderer->FlipX(true);
        // LOG_INFO(gameObject->GetName() << ": sprite flip Right");
    } else if (input->GetHorizontalAxis() > 0) {
        spriteRenderer->FlipX(false);
        // LOG_INFO(gameObject->GetName() << ": sprite flip Left");
    }
}

void DirectionComponent::Render() {}
}  // namespace EngineCore
