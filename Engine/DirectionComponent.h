#pragma once
#include "GameObject.h"
#include "SpriteRendererComponent.h"
#include "InputComponent.h"

namespace EngineCore
{
	class DirectionComponent : public Component
	{
	public:
		DirectionComponent(GameObject* gameObject);

		void Update(float deltaTime) override;
		void Render() override;
	private:
		InputComponent* input;
		SpriteRendererComponent* spriteRenderer;
	};
}
