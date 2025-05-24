#include "DeveloperLevel.h"

#include "EnemyAIComponent.h"


using namespace EngineCore;

namespace Rogalique
{
    void DeveloperLevel::Start()
    {
        LOG_INFO("!Started " << levelName);
        float spritePanelWidth = 100;
        float spritePanelHeight = 100;
        
        for (int y = 0; y < levelWidth; y++)
        {
            for (int x = 0; x < levelHeight; x++)
            {
                if (y == 0 || y == levelWidth - 1 || x == 0 || x == levelHeight - 1)
                {
                    wall = std::make_unique<Wall>(EngineCore::Vector2Df{ spritePanelWidth * x, spritePanelHeight * y });
                }
                else
                {
                    floor = std::make_unique<Floor>(EngineCore::Vector2Df{ spritePanelWidth * x, spritePanelHeight * y });
                }

            }
        }

        player = std::make_unique<Player>(std::forward<EngineCore::Vector2Df>({ 200, 200 }));
        if (player) {LOG_INFO(player->GetGameObject()->GetName() << " declared at level: " << levelName)}else{LOG_WARN("Player not spawn at level: " << levelName)}
        enemy = std::make_unique<Enemy>(std::forward<EngineCore::Vector2Df>({ 450, 1600 }));
        if (enemy) {LOG_INFO(enemy->GetGameObject()->GetName() << " declared at level: " << levelName)}else{LOG_WARN("Enemy not spawn at level: " << levelName)}
        music = std::make_unique<Music>("soundtrack");
        if (music) {LOG_INFO("Music Load at level: " << levelName)}else{LOG_WARN("Music not Load at level: " << levelName)}
    }
    void DeveloperLevel::Restart()
    {
        Stop();
        Start();
        LOG_INFO("!Restarted " << levelName);
    }
    void DeveloperLevel::Stop()
    {
        LOG_INFO("!Stopped " << levelName);
        GameWorld::Instance()->Clear();
    }


}