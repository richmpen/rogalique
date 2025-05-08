#include "pch.h"
#include "DirectionComponent.h"


namespace EngineCore {

	DirectionComponent::DirectionComponent(GameObject* gameObject)
		: Component(gameObject)
	{
		input = gameObject->GetComponent<InputComponent>();
		spriteRenderer = gameObject->GetComponent<SpriteRendererComponent>();
	}

	void DirectionComponent::Update(float deltaTime)
	{
		if (input->GetHorizontalAxis() < 0)
		{
			spriteRenderer->FlipX(true);
			// std::cout << "flipZ" << std::endl;
		}
		else if (input->GetHorizontalAxis() > 0)
		{
			spriteRenderer->FlipX(false);
			// std::cout << "flipY" << std::endl;
		}
	}

	void DirectionComponent::Render()
	{
	}
}

