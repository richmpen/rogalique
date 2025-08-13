#pragma once

#include "../Systems/PhysicsSystem.h"
#include "GameObject.h"

namespace EngineCore {
class GameWorld {
   public:
    static GameWorld* Instance();

    void Update(float deltaTime);
    void FixedUpdate(float deltaTime);
    void Render();
    void LateUpdate();

    GameObject* CreateGameObject();
    GameObject* CreateGameObject(std::string name);
    GameObject* FindGameObjectByName(const std::string& name);
    GameObject* FindPlayer();
    void DestroyGameObject(GameObject* gameObject);
    void Clear();

    void Print() const;

    const std::vector<GameObject*>& GetAllGameObjects() const {
        return gameObjects;
    }

    static void SetPaused(bool paused) { isPaused = paused; }
    static bool IsPaused() { return isPaused; }

   private:
    GameWorld() {}
    ~GameWorld() {}

    GameWorld(GameWorld const&) = delete;
    GameWorld& operator=(GameWorld const&) = delete;

    float fixedCounter = 0.f;
    static bool isPaused;

    std::vector<GameObject*> gameObjects = {};
    std::vector<GameObject*> markedToDestroyGameObjects = {};

    void DestroyGameObjectImmediate(GameObject* gameObject);
};
}  // namespace EngineCore