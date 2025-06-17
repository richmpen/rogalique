#include "pch.h"

#include "Component.h"

#include <iostream>

namespace EngineCore {
Component::Component(GameObject* gameObject) : gameObject(gameObject) {}
Component::~Component() { LOG_INFO("Deleted component: " << this); }

GameObject* Component::GetGameObject() { return gameObject; }
}  // namespace EngineCore