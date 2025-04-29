#pragma once
#include "Component.h"
#include <SFML/Graphics.hpp>

namespace EngineCore
{
    class InputComponent : public Component
    {
    public:
        InputComponent(GameObject* gameObject);

        void Update(float deltaTime) override;
        void Render() override;

        float GetHorizontalAxis() const;
        float GetVerticalAxis() const;

        private:
        float horizontalAxis = 0.f;
        float verticalAxis = 0.f;
    };

}
