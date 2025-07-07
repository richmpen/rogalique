#include "pch.h"

#include "AnimationComponent.h"

namespace EngineCore {

AnimationComponent::AnimationComponent(GameObject* gameObject)
    : Component(gameObject) {
    renderer = gameObject->GetComponent<SpriteRendererComponent>();

    if (renderer == nullptr) {
        LOG_WARN("Need renderer component for movement animation")
        gameObject->RemoveComponent(this);
    }
}

void AnimationComponent::Initialize(const std::string& textureMapName,
                                    float newFramerate) {
    for (int i = 0; i < ResourceSystem::Instance()->GetTextureMapElementsCount(
                            textureMapName);
         i++) {
        textureMap.push_back(
            ResourceSystem::Instance()->GetTextureMapElementShared(
                textureMapName, i));
    }

    secondsForFrame = 1.f / newFramerate;
}

void AnimationComponent::Update(float deltaTime) {
    counter += deltaTime;
    if (counter > secondsForFrame) {
        counter -= secondsForFrame;
        frame++;

        if (frame == textureMap.size()) {
            frame = 0;
        }

        renderer->SetTexture(*textureMap[frame]);
    }
}

void AnimationComponent::Render() {}

}  // namespace EngineCore
