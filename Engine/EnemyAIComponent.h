#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Vector.h"

namespace EngineCore
{
    
    class EnemyAIComponent : public Component
    {
    public:
        EnemyAIComponent(GameObject* gameObject);
        void Update(float deltaTime) override;
        void Render() override;
    private:
        GameObject* playerObject;
        float chaseDistance;
        float speed;
    };
}
