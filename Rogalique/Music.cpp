#include "Music.h"

namespace Rogalique
{
    Music::Music(const std::string& soundName)
    {
        auto gameObject = EngineCore::GameWorld::Instance()->CreateGameObject(soundName);
        auto music = gameObject->AddComponent<EngineCore::SoundComponent>();
        music->SetSound(*EngineCore::ResourceSystem::Instance()->GetSound(soundName));
        music->SetLoop(true);
        music->Start();
    }

}
