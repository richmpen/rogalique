#include "DeveloperLevel.h"


using namespace EngineCore;

namespace Rogalique
{
    void DeveloperLevel::Start()
    {
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
        enemy = std::make_unique<Enemy>(std::forward<EngineCore::Vector2Df>({ 450, 1600 }));
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