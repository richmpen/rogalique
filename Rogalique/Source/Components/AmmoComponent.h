#pragma once
#include "Component.h"

namespace Rogalique {

class AmmoComponent : public EngineCore::Component {
public:
    AmmoComponent(EngineCore::GameObject* gameObject);
    void Spending(int count);
    void AddAmmo(int count);
    void SetMaxAmmo(int newMaxAmmoCount);
    void SetAmmoInClip(int newAmmoInClip);
    void Reloading();
    
    int GetAmmo() const;
    int GetMaxAmmo() const;
    int GetAmmoInClip() const;
    
    void Update(float deltaTime) override;
    void Render() override;

private:
    int currentAmmo = 0;
    int maxAmmo = 0;
    int ammoInClip = 0;
};

}  // namespace Rogalique
