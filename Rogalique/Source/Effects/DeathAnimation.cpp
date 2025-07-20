#include "DeathAnimation.h"

#include "AnimationComponent.h"
#include "EnemyAIComponent.h"
#include "GameSettings.h"
#include "HealthComponent.h"
#include "ResourceSystem.h"

namespace Rogalique {

DeathAnimation::DeathAnimation(EngineCore::GameObject* gameObject)
    : Component(gameObject) {
    renderer = gameObject->GetComponent<EngineCore::SpriteRendererComponent>();
    collider = gameObject->GetComponent<EngineCore::SpriteColliderComponent>();
}

void DeathAnimation::Start() {
    isDeath = true;
    timer = SETTINGS.DEATH_TIMER;
    if (renderer) {
        renderer->SetTexture(
            *EngineCore::ResourceSystem::Instance()->GetTextureMapElementShared(
                "demonDeath", 0));
        renderer->SetPixelSize(100, 100);
    }
    auto aiComponent = gameObject->GetComponent<EnemyAIComponent>();
    auto rigidbody = gameObject->GetComponent<EngineCore::RigidbodyComponent>();
    if (aiComponent) {
        gameObject->AddComponent<EngineCore::AnimationComponent>();
        gameObject->GetComponent<EngineCore::AnimationComponent>()->Initialize(
            "demonDeath", SETTINGS.DEATH_TIMER * 5);
        aiComponent->SetMoveSpeed(0.0f);
        rigidbody->SetKinematic(true);
        gameObject->RemoveComponent(collider);
    }
}

void DeathAnimation::Update(float deltaTime) {
    if (IsDeath()) { 
        SetTimer(GetTimer() - deltaTime);
        if (GetTimer() <= 0.0f) {
            gameObject->GetComponent<HealthComponent>()->Die();
        }
    }
}

void DeathAnimation::Render() {}

void DeathAnimation::SetTimer(float count) {
    timer = count;
}

float DeathAnimation::GetTimer() const { return timer; }

bool DeathAnimation::IsDeath() { return isDeath; }
}  // namespace Rogalique