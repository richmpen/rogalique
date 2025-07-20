#pragma once
#include "GameObject.h"
#include "MoveComponent.h"
#include "ResourceSystem.h"
#include "SpriteRendererComponent.h"

namespace EngineCore {
class AnimationComponent : public Component {
   public:
    AnimationComponent(GameObject* gameObject);

    void Initialize(const std::string& textureMapName, float newFramerate);

    void Update(float deltaTime) override;
    void Render() override;

   private:
    SpriteRendererComponent* renderer;

    std::vector<const sf::Texture*> textureMap;
    float secondsForFrame = 0.f;

    float counter = 0.f;
    int frame = 0;
};
}  // namespace EngineCore
