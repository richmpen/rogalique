#include "pch.h"
#include "SoundComponent.h"

#include "GameObject.h"


namespace EngineCore
{
    SoundComponent::SoundComponent(GameObject* gameObject) : Component(gameObject)
    {
        sound = new sf::Sound();
        if (!sound) {
            LOG_WARN("SoundComponent dont add to: " << gameObject->GetName());
        }
        LOG_INFO("Created SoundComponent for GameObject: " << gameObject->GetName());
    }

    SoundComponent::~SoundComponent()
    {
        delete sound;
    }

    void SoundComponent::Update(float deltaTime){}

    void SoundComponent::Render(){}

    void SoundComponent::SetSound(const sf::SoundBuffer& newSound)
    {
        LOG_INFO("Initializing sound: " << &newSound);
        sound->setBuffer(newSound);
    }
    
    void SoundComponent::Start()
    {
        LOG_INFO("Sound Play")
        sound->play();
    }
    
    void SoundComponent::Stop()
    {
        LOG_INFO("Sound Stop")
        sound->stop();
    }
    
    void SoundComponent::SetVolume(float volume)
    {
        LOG_INFO("Volume: "<<volume<<"%")
        sound->setVolume(volume);
    }
    
    void SoundComponent::SetLoop(bool loop)
    {
        sound->setLoop(loop);
    }

}
