#include "pch.h"
#include "InputComponent.h"
#include "iostream"
#include "TransformComponent.h"

namespace EngineCore
{
    InputComponent::InputComponent(GameObject* gameObject) : Component(gameObject)
    {

    }

    void InputComponent::Update(float deltaTime)
    {
        verticalAxis = 0.f;
        horizontalAxis = 0.f;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            verticalAxis += 1.0f;
            //std::cout << "Up" << std::endl;

        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            verticalAxis -= 1.0f;
            //std::cout << "Down" << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            horizontalAxis += 1.0f;
            //std::cout << "Right" << std::endl;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            horizontalAxis -= 1.0f;
            //std::cout << "Left" << std::endl;
        }
        
    }

    void InputComponent::Render()
    {
        
    }

    float InputComponent::GetHorizontalAxis() const
    {
        return horizontalAxis;
    }
    float InputComponent::GetVerticalAxis() const
    {
        return verticalAxis;
    }

}