#pragma once
#include "EnemyAIComponent.h"
#include "GameObject.h"
#include "InputComponent.h"
#include "SpriteMovementAnimationComponent.h"

#include "SpriteRendererComponent.h"

namespace Rogalique {

enum class directionEnum {
    None = 0,
    Up,
    Right,
    Left,
    Down,
};

class DirectionComponent : public EngineCore::Component {
   public:
    DirectionComponent(EngineCore::GameObject* gameObject);
    void SwitchDirection(directionEnum dir);
    directionEnum GetCurrentDirection() const;

    void AddDirectionMoveAnimation(directionEnum dir,int firstFrame,int lastFrame, bool FlipX);
    void Update(float deltaTime) override;
    void Render() override;

   private:
    directionEnum direction = directionEnum::None;
    EngineCore::GameObject* playerObject;
    EngineCore::InputComponent* input;
    EngineCore::SpriteRendererComponent* spriteRenderer;
    EngineCore::TransformComponent* transform;
    EnemyAIComponent* enemyAI;
    EngineCore::SpriteMovementAnimationComponent* moveAnimation;
    std::map<directionEnum, EngineCore::AnimationParams> animationMap;
};
}  // namespace Rogalique
