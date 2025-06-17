#include "pch.h"

#include "SpriteColliderComponent.h"

namespace EngineCore {
SpriteColliderComponent::SpriteColliderComponent(GameObject* gameObject)
    : ColliderComponent(gameObject) {
    auto spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
    if (spriteRenderer == nullptr) {
        LOG_ERROR("SpriteRenderer required to SpriteCollider.");
        gameObject->RemoveComponent(this);
        return;
    }

    sprite = gameObject->GetComponent<SpriteRendererComponent>()->GetSprite();
    PhysicsSystem::Instance()->Subscribe(this);
}
SpriteColliderComponent::~SpriteColliderComponent() {
    if (&bounds != nullptr) {
        std::destroy_at(&bounds);
    }
    PhysicsSystem::Instance()->Unsubscribe(this);
}

void SpriteColliderComponent::Update(float deltaTime) {
    bounds = sprite->getGlobalBounds();
}
void SpriteColliderComponent::Render() {}
}  // namespace EngineCore