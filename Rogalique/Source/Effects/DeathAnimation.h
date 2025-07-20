#pragma once
#include "AnimationComponent.h"
#include "Component.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"

namespace Rogalique {

class DeathAnimation : public EngineCore::Component {
   public:
    DeathAnimation(EngineCore::GameObject* gameObject);
    void Start();
    void Update(float deltaTime) override;
    void Render() override;
    void SetTimer(float count);
    float GetTimer() const;
    bool IsDeath();

   private:
    float timer = 0.0f;
    bool isDeath = false;

    EngineCore::SpriteColliderComponent* collider;
    EngineCore::SpriteRendererComponent* renderer;
    EngineCore::AnimationComponent* animator;
};
}  // namespace Rogalique
