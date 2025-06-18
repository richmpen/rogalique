
#include "DirectionComponent.h"

namespace Rogalique {

DirectionComponent::DirectionComponent(EngineCore::GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<EngineCore::InputComponent>();
    spriteRenderer =
        gameObject->GetComponent<EngineCore::SpriteRendererComponent>();
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
}  // namespace Rogalique
