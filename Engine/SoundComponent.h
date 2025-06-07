#pragma once
#include "Component.h"

#include "SFML/Audio/Sound.hpp"
#include "SFML/Audio/SoundBuffer.hpp"

namespace EngineCore {
class SoundComponent : public Component {
   public:
    SoundComponent(GameObject* gameObject);
    ~SoundComponent();

    void Update(float deltaTime) override;
    void Render() override;

    void SetSound(const sf::SoundBuffer& newSound);
    void Start();
    void Stop();
    void SetVolume(float volume);
    void SetLoop(bool loop);

   private:
    sf::Sound* sound;
    float volume;
    bool loop;
};
}  // namespace EngineCore
