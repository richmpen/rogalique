#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Vector.h"

namespace EngineCore {

class EnemyAIComponent : public Component {
   public:
    EnemyAIComponent(GameObject* gameObject);
    void Update(float deltaTime) override;
    void Render() override;
    void SetMoveSpeed(float newSpeed) { speed = newSpeed; };

   private:
    GameObject* playerObject;
    float chaseDistance;
    float speed;
};
}  // namespace EngineCore
