#pragma once

#include <GameObject.h>
#include <GameWorld.h>
#include <ResourceSystem.h>
#include <SoundComponent.h>

namespace Rogalique {
class Music {
   public:
    Music(const std::string& soundName);
    EngineCore::GameObject* GetGameObject();

   private:
    EngineCore::GameObject* gameObject;
};
}  // namespace Rogalique
