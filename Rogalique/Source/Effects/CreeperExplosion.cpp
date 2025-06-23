#include "CreeperExplosion.h"

#include "EnemyAIComponent.h"
#include "GameSettings.h"
#include "HealthComponent.h"
#include "ResourceSystem.h"

namespace Rogalique {

CreeperExplosion::CreeperExplosion(EngineCore::GameObject* gameObject)
    : Component(gameObject) {
    renderer = gameObject->GetComponent<EngineCore::SpriteRendererComponent>();
    collider = gameObject->GetComponent<EngineCore::SpriteColliderComponent>();
}

void CreeperExplosion::StartCreeperExplosion() {
    isCreeperExploding = true;
    explosionTimer = SETTINGS.CREEPER_EXPLOSION_TIMER;  // 2 seconds to death
    if (renderer) {
        renderer->SetTexture(
            *EngineCore::ResourceSystem::Instance()->GetTextureShared(
                "creeperExplosion"));
    }
    auto aiComponent = gameObject->GetComponent<EnemyAIComponent>();
    auto rigidbody = gameObject->GetComponent<EngineCore::RigidbodyComponent>();
    if (aiComponent) {
        aiComponent->SetMoveSpeed(0.0f);
        rigidbody->SetKinematic(true);
        gameObject->RemoveComponent(collider);
    }
}

void CreeperExplosion::Update(float deltaTime) {
    if (IsExploding()) {  //+ check for the presence of CreeperExplosion
                          //Component
        SetExplosionTimer(GetExplosionTimer() - deltaTime);
        if (GetExplosionTimer() <= 0.0f) {
            gameObject->GetComponent<HealthComponent>()->Die();
        }
    }
}

void CreeperExplosion::Render() {}

void CreeperExplosion::SetExplosionTimer(float count) {
    explosionTimer = count;
}

float CreeperExplosion::GetExplosionTimer() const { return explosionTimer; }

bool CreeperExplosion::IsExploding() { return isCreeperExploding; }
}  // namespace Rogalique