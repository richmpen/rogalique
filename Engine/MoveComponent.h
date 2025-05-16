 #pragma once
 #include "InputComponent.h"
 #include "GameObject.h"

 namespace EngineCore {

 	class MoveComponent : public Component
 	{
 		public:
 		MoveComponent(GameObject* gameObject);
 		float GetSpeed() const {return speed;}
 		void SetSpeed(float newSpeed){speed = newSpeed;}
 		void Update(float deltaTime) override;
 		void Render() override;
 	private:
 		float speed;
 		InputComponent* input;
 		TransformComponent* transform;
 	};

 }