#pragma once
#include "GameObject.h"
#include "MoveComponent.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"

namespace EngineCore
{
class SpriteMovementAnimationComponent : public Component
{
public:
    SpriteMovementAnimationComponent(GameObject* gameObject);

    void Initialize(const std::string& textureMapName, float newFramerate);

    void Update(float deltaTime) override;
    void Render() override;
private:
    MoveComponent* movement;
    SpriteRendererComponent* renderer;

    std::vector<const sf::Texture*> textureMap;
    float secondsForFrame = 0.f;

    float counter = 0.f;
    int frame = 0;
};
}
