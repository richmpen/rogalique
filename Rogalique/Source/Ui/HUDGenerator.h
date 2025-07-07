#pragma once
#include "DeveloperLevel.h"

namespace Rogalique {

class HUDGenerator {
   public:
    HUDGenerator(const std::shared_ptr<UiManager>& shared,
                 DeveloperLevel* level, GameObject* gameObject);
    void Generate();

   private:
    DeveloperLevel* level;
    std::shared_ptr<UiManager> uiManager;
    GameObject* gameObject;
};
}  // namespace Rogalique
