#pragma once
#include "DeveloperLevel.h"
#include "Ui/UiElement.h"
#include "Ui/UiManager.h"

namespace Rogalique {

class HUDGenerator {
   public:
    HUDGenerator(UiManager* manager, EngineCore::GameObject* gameObject);
    void Generate();

   private:
    UiManager* uiManager;
    EngineCore::GameObject* gameObject;
};
}  // namespace Rogalique
