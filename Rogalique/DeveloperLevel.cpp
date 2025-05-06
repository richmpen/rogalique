#include "DeveloperLevel.h"

using namespace EngineCore;

namespace Rogalique
{
    void DeveloperLevel::Start()
    {
        player = std::make_unique<Player>(std::forward<EngineCore::Vector2Df>({ 0, 0 }));
        music = std::make_unique<Music>("soundtrack");
    }
    void DeveloperLevel::Restart()
    {
        Stop();
        Start();
    }
    void DeveloperLevel::Stop()
    {
        GameWorld::Instance()->Clear();
    }

}