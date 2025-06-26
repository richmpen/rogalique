#include "pch.h"
#include "SpriteMovementAnimationComponent.h"

namespace EngineCore {

SpriteMovementAnimationComponent::SpriteMovementAnimationComponent(GameObject* gameObject)
        : Component(gameObject)
{
    movement = gameObject->GetComponent<MoveComponent>();
    renderer = gameObject->GetComponent<SpriteRendererComponent>();

    if (movement == nullptr)
    {
        LOG_WARN("Need movement component for movement animation")
        gameObject->RemoveComponent(this);
    }
    else if (renderer == nullptr)
    {
        LOG_WARN("Need renderer component for movement animation")
        gameObject->RemoveComponent(this);
    }
}

void SpriteMovementAnimationComponent::Initialize(const std::string& textureMapName, float newFramerate)
{
    for (int i = 0; i < ResourceSystem::Instance()->GetTextureMapElementsCount(textureMapName); i++)
    {
        textureMap.push_back(ResourceSystem::Instance()->GetTextureMapElementShared(textureMapName, i));
    }

    secondsForFrame = 1.f / newFramerate;
}

void SpriteMovementAnimationComponent::Update(float deltaTime)
{
    if (movement->GetAccelerationSquared() == 0.f)
    {
        if (counter > 0)
        {
            counter = 0;
            frame = 0;
            renderer->SetTexture(*textureMap[0]);
        }
        return;
    }

    counter += deltaTime;
    if (counter > secondsForFrame)
    {
        counter = 0;
        frame++;

        if (frame == textureMap.size())
        {
            frame = 0;
        }

        renderer->SetTexture(*textureMap[frame]);
    }
}

void SpriteMovementAnimationComponent::Render()
{
}

}


