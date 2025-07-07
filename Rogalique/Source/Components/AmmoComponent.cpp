#include "AmmoComponent.h"

#include "GameObject.h"
#include "GameWorld.h"

namespace Rogalique {

AmmoComponent::AmmoComponent(EngineCore::GameObject* gameObject)
    : Component(gameObject) {}

void AmmoComponent::Spending(int count) {
    if (currentAmmo > 0) {
        currentAmmo -= count;
        // LOG_INFO("Spending ammo : " << currentAmmo)
    }
}

void AmmoComponent::AddAmmo(int count) {
    if (currentAmmo < maxAmmo) {
        currentAmmo += count;
        // LOG_INFO("Add Ammo:" << currentAmmo)
    }
    if (count > maxAmmo - currentAmmo) {
        ammoInClip += count - (maxAmmo - currentAmmo);
        currentAmmo = maxAmmo;
    }
}

void AmmoComponent::SetMaxAmmo(int newMaxAmmoCount) {
    maxAmmo = newMaxAmmoCount;
}

void AmmoComponent::SetAmmoInClip(int newAmmoInClip) {
    ammoInClip = newAmmoInClip;
}

void AmmoComponent::Reloading() {
    if (ammoInClip > 0 && currentAmmo < maxAmmo) {
        if (ammoInClip >= maxAmmo) {
            ammoInClip -= maxAmmo;
            ammoInClip += currentAmmo;
            currentAmmo = maxAmmo;
        } else {
            int lackOf = maxAmmo -= currentAmmo;
            ammoInClip -= lackOf;
            currentAmmo += lackOf;
            if (lackOf > ammoInClip) {
                ammoInClip = 0;
            }
        }
    }
}

int AmmoComponent::GetAmmo() const { return currentAmmo; }

int AmmoComponent::GetMaxAmmo() const { return maxAmmo; }

int AmmoComponent::GetAmmoInClip() const { return ammoInClip; }

void AmmoComponent::Update(float deltaTime) {
    if (currentAmmo <= 0 && ammoInClip > 0) {
        Reloading();
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
        Reloading();
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        Spending(1);
    }
}

void AmmoComponent::Render() {}
}  // namespace Rogalique