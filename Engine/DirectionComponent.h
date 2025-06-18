#pragma once
#include "GameObject.h"
#include "InputComponent.h"
#include "SpriteRendererComponent.h"

namespace Rogalique {
class DirectionComponent : public EngineCore::Component {
   public:
    DirectionComponent(EngineCore::GameObject* gameObject);

    void Update(float deltaTime) override;
    void Render() override;

   private:
    EngineCore::InputComponent* input;
    EngineCore::SpriteRendererComponent* spriteRenderer;
};
}  // namespace Rogalique
