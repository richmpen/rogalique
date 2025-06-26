#pragma once
#include "GameObject.h"
#include "InputComponent.h"

namespace EngineCore {

class MoveComponent : public Component {
   public:
    MoveComponent(GameObject* gameObject);
    float GetSpeed() const { return speed; }
    void SetSpeed(float newSpeed) { speed = newSpeed; }
    float GetAccelerationSquared() const;
    void Update(float deltaTime) override;
    void Render() override;
    const Vector2Df& GetAcceleration() const { return acceleration; }
   private:
    float speed;
    Vector2Df acceleration = { 0, 0 };
    Vector2Df previousPosition = { 0, 0 };
    InputComponent* input;
    TransformComponent* transform;
    
};

}  // namespace EngineCore