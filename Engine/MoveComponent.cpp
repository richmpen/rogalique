 #include "pch.h"
 #include "MoveComponent.h"

 namespace EngineCore
 {
     MoveComponent::MoveComponent(GameObject* gameObject) : Component(gameObject)
     {
         input = gameObject->GetComponent<InputComponent>();
         transform = gameObject->GetComponent<TransformComponent>();
     }

     void MoveComponent::Update(float deltaTime)
     {
         transform->MoveBy(speed * deltaTime * Vector2Df{ input->GetHorizontalAxis(), input->GetVerticalAxis() });
     }

     void MoveComponent::Render()
     {
     }
 }
