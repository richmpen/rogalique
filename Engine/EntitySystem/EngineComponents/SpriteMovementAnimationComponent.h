#pragma once
#include "GameObject.h"
#include "MoveComponent.h"
#include "SpriteRendererComponent.h"
#include "ResourceSystem.h"

namespace EngineCore
{

struct AnimationParams {
    int startFrame;
    int endFrame;
    bool flipX;
};

class SpriteMovementAnimationComponent : public Component
{
public:
    SpriteMovementAnimationComponent(GameObject* gameObject);

    void Initialize(const std::string& textureMapName, float newFramerate);
    void PlayAnimation(int startFrame, int endFrame);
    void Update(float deltaTime) override;
    void Render() override;
private:
    std::pair<int, int> animationRange;
    InputComponent* input;
    MoveComponent* movement;
    SpriteRendererComponent* renderer;
    std::vector<const sf::Texture*> textureMap;
    float secondsForFrame = 0.f;

    float counter = 0.f;
    int frame = 0;
};
}
