#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Vector.h"

namespace Rogalique {

class EnemyAIComponent : public EngineCore::Component {
   public:
    EnemyAIComponent(EngineCore::GameObject* gameObject);
    void Update(float deltaTime) override;
    void Render() override;
    void SetMoveSpeed(float newSpeed) { speed = newSpeed; };

   private:
    EngineCore::GameObject* playerObject;
    float chaseDistance;
    float speed;
};
}  // namespace Rogalique
