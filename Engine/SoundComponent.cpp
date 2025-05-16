#include "pch.h"
#include "SoundComponent.h"


namespace EngineCore
{
    SoundComponent::SoundComponent(GameObject* gameObject) : Component(gameObject)
    {
        sound = new sf::Sound();
    }

    SoundComponent::~SoundComponent()
    {
        delete sound;
    }

    void SoundComponent::Update(float deltaTime){}

    void SoundComponent::Render(){}

    void SoundComponent::SetSound(const sf::SoundBuffer& newSound)
    {
        sound->setBuffer(newSound);
    }
    
    void SoundComponent::Start()
    {
        sound->play();
    }
    
    void SoundComponent::Stop()
    {
        sound->stop();
    }
    
    void SoundComponent::SetVolume(float volume)
    {
        sound->setVolume(volume);
    }
    
    void SoundComponent::SetLoop(bool loop)
    {
        sound->setLoop(loop);
    }

}