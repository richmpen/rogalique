#pragma once
#include "AnimationComponent.h"
#include "Component.h"
#include "SpriteColliderComponent.h"
#include "SpriteRendererComponent.h"

namespace Rogalique {

class CreeperExplosion : public EngineCore::Component {
   public:
    CreeperExplosion(EngineCore::GameObject* gameObject);
    void StartCreeperExplosion();
    void Update(float deltaTime) override;
    void Render() override;
    void SetExplosionTimer(float count);
    float GetExplosionTimer() const;
    bool IsExploding();

   private:
    float explosionTimer = 0.0f;
    bool isCreeperExploding = false;

    EngineCore::SpriteColliderComponent* collider;
    EngineCore::SpriteRendererComponent* renderer;
    EngineCore::AnimationComponent* animator;
};
}  // namespace Rogalique
