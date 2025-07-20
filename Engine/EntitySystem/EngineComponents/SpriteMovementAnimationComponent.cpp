#include "pch.h"

#include "SpriteMovementAnimationComponent.h"

namespace EngineCore {

SpriteMovementAnimationComponent::SpriteMovementAnimationComponent(
    GameObject* gameObject)
    : Component(gameObject) {
    input = gameObject->GetComponent<InputComponent>();
    movement = gameObject->GetComponent<MoveComponent>();
    renderer = gameObject->GetComponent<SpriteRendererComponent>();
    if (movement == nullptr) {
        LOG_WARN("Need movement component for movement animation")
        gameObject->RemoveComponent(this);
    } else if (renderer == nullptr) {
        LOG_WARN("Need renderer component for movement animation")
        gameObject->RemoveComponent(this);
    } else if (input == nullptr) {
        LOG_WARN("Need input component for movement animation")
    }
}

void SpriteMovementAnimationComponent::PlayAnimation(int startFrame,
                                                     int endFrame) {
    if (textureMap.empty() || startFrame < 0 ||
        endFrame >= static_cast<int>(textureMap.size()) ||
        startFrame > endFrame) {
        LOG_ERROR("Invalid animation range: startFrame="
                  << startFrame << ", endFrame=" << endFrame
                  << ", textureMap.size()=" << textureMap.size());
        return;
    }
    frame = startFrame;
    animationRange = {startFrame, endFrame};
    renderer->SetTexture(*textureMap[frame]);
}

void SpriteMovementAnimationComponent::Initialize(
    const std::string& textureMapName, float newFramerate) {
    for (int i = 0; i < ResourceSystem::Instance()->GetTextureMapElementsCount(
                            textureMapName);
         i++) {
        textureMap.push_back(
            ResourceSystem::Instance()->GetTextureMapElementShared(
                textureMapName, i));
    }

    secondsForFrame = 1.f / newFramerate;
}

void SpriteMovementAnimationComponent::Update(float deltaTime) {
    if (!movement || !renderer) {
        return;
    }
    if (movement->GetAccelerationSquared() == 0.f) {
        if (counter > 0) {
            counter = 0;
            frame = 0;
            renderer->SetTexture(*textureMap[0]);
        }
        return;
    }

    counter += deltaTime;
    if (counter > secondsForFrame) {
        counter = 0;
        frame++;
        if (frame > animationRange.second) {
            frame = animationRange.first;
        }
        renderer->SetTexture(*textureMap[frame]);
    }
}

void SpriteMovementAnimationComponent::Render() {}

}  // namespace EngineCore
