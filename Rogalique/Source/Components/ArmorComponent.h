#pragma once
#include "Component.h"

namespace Rogalique {

class ArmorComponent : public EngineCore::Component {
public:
    ArmorComponent(EngineCore::GameObject* gameObject);
    void TakeDamage(int damageValue);
    void SetArmor(int armor);
    int GetArmor() const;
    void SetMaxArmor(int newMaxArmor);
    int GetMaxArmor() const;
    void Update(float deltaTime) override;
    void Render() override;

private:
    int armor = 0;
    int maxArmor = 0;
};

}  // namespace Rogalique
