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
                    // LoadObjectCheck(wall);
                }
                else
                {
                    floor = std::make_unique<Floor>(EngineCore::Vector2Df{ spritePanelWidth * x, spritePanelHeight * y });
                    // LoadObjectCheck(floor);
                }

            }
        }

        player = std::make_unique<Player>(std::forward<EngineCore::Vector2Df>({ 200, 200 }),EngineCore::EnemyType::Player, 15, 100);
        LoadObjectCheck(player);
        enemy = std::make_unique<Enemy>(std::forward<EngineCore::Vector2Df>({ 450, 1600 }),EngineCore::EnemyType::Enemy,10, 50);
        LoadObjectCheck(enemy);
        music = std::make_unique<Music>("soundtrack");
        LoadObjectCheck(music);
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