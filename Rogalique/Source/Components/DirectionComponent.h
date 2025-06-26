#pragma once
#include "EnemyAIComponent.h"
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
    EngineCore::GameObject* playerObject;
    EngineCore::InputComponent* input;
    EngineCore::SpriteRendererComponent* spriteRenderer;
    EngineCore::TransformComponent* transform;
    EnemyAIComponent* enemyAI;
};
}  // namespace Rogalique
