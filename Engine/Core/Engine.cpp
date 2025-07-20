#include "pch.h"

#include "Engine.h"

#include "GameStateManager.h"
#include "GameWorld.h"
#include "RenderSystem.h"

#include <cassert>
#include <iostream>

namespace EngineCore {
Engine* Engine::Instance() {
    static Engine instance;
    return &instance;
}

Engine::Engine() {
    unsigned int seed = (unsigned int)time(nullptr);
    srand(seed);
    setupLogger();
    LOG_INFO("Setup Logger init!");
}

void Engine::Run() {
    sf::Clock gameClock;
    sf::Event event;

    LOG_INFO("Game started");
    

    while (RenderSystem::Instance()->GetMainWindow().isOpen()) {
        sf::Time dt = gameClock.restart();
        float deltaTime = dt.asSeconds();

        while (RenderSystem::Instance()->GetMainWindow().pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                RenderSystem::Instance()->GetMainWindow().close();
            }
            GameStateManager::Instance()->HandleEvent(event);
        }

        if (!RenderSystem::Instance()->GetMainWindow().isOpen()) {
            LOG_WARN("need use game-save logic")
            LOG_INFO("Game stopped");
            break;
        }

        GameStateManager::Instance()->Update(deltaTime);

        RenderSystem::Instance()->GetMainWindow().clear();

        GameWorld::Instance()->Update(deltaTime);
        GameWorld::Instance()->FixedUpdate(deltaTime);
        
        GameWorld::Instance()->Render();
        
        GameStateManager::Instance()->Render();
        
        GameWorld::Instance()->LateUpdate();

        RenderSystem::Instance()->GetMainWindow().display();
    }
}

void Engine::setupLogger() {
    auto logger = std::make_shared<Logger>();
    logger->addSink(std::make_shared<ConsoleSink>());
    logger->addSink(std::make_shared<FileSink>("Source/Logs/mainLog.txt"));

    LoggerRegistry::getInstance().registerLogger("global", logger);
    LoggerRegistry::getInstance().setDefaultLogger(logger);
    assert(logger && "Logger registration failed!");
}
}  // namespace EngineCore