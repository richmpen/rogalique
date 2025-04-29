#include "pch.h"
#include "CameraComponent.h"

#include <iostream>

#include "TransformComponent.h"

namespace EngineCore
{
    CameraComponent::CameraComponent(GameObject* gameObject) : Component(gameObject)
    {
        view = new sf::View(sf::FloatRect(0, 0, 800, -600));
        transform = gameObject->GetComponent<TransformComponent>();
    }

    CameraComponent::~CameraComponent()
    {
        delete view;
    }

    void CameraComponent::Update(float deltaTime)
    {
        auto position = transform->GetWorldPosition();
        auto rotation = transform->GetWorldRotation();

        view->setCenter(Convert<sf::Vector2f, Vector2Df>(position));
        view->setRotation(rotation);
        window->setView(*view);
    }

    void CameraComponent::Render()
    {
        if (window == nullptr)
        {
            std::cout << "Null window Render." << std::endl;
        }
    }

    void CameraComponent::SetBaseResolution(int width, int height)
    {
        view->reset(sf::FloatRect(0, 0, width, -height));
    }

    void CameraComponent::SetWindow(sf::RenderWindow* newWindow)
    {
        window = newWindow;
    }

    void CameraComponent::ZoomBy(float newZoom)
    {
        if (newZoom <= 0)
        {
            std::cout << "Not Allowed zoom lesser or equal than zero" << std::endl;
            return;
        }
        view->zoom(newZoom);
    }


}
