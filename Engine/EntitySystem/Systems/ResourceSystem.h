#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>

namespace EngineCore {
class ResourceSystem {
   public:
    static ResourceSystem* Instance();

    void LoadTexture(const std::string& name, std::string sourcePath,
                     bool isSmooth = true);
    const sf::Texture* GetTextureShared(const std::string& name) const;
    sf::Texture* GetTextureCopy(const std::string& name) const;
    void DeleteSharedTexture(const std::string& name);

    void LoadTextureMap(const std::string& name, std::string sourcePath,
                        sf::Vector2u elementPixelSize, int totalElements,
                        bool isSmooth = true);
    const sf::Texture* GetTextureMapElementShared(const std::string& name,
                                                  int elementIndex) const;
    sf::Texture* GetTextureMapElementCopy(const std::string& name,
                                          int elementIndex) const;
    int GetTextureMapElementsCount(const std::string& name) const;
    void DeleteSharedTextureMap(const std::string& name);

    void LoadSound(const std::string& name, std::string sourcePath);
    void DeleteSound(const std::string& name);
    const sf::SoundBuffer* GetSound(const std::string& name) const;

    void LoadFont(const std::string& name, std::string sourcePath);
    const sf::Font* GetFont(const std::string& name) const;
    void Clear();

   private:
    std::map<std::string, sf::Texture*> textures;
    std::map<std::string, std::vector<sf::Texture*>> textureMaps;
    std::map<std::string, sf::SoundBuffer*> sounds;
    std::map<std::string, sf::Font*> fonts;

    ResourceSystem() {}
    ~ResourceSystem() {}

    ResourceSystem(ResourceSystem const&) = delete;
    ResourceSystem& operator=(ResourceSystem const&) = delete;

    void DeleteAllTextures();
    void DeleteAllTextureMaps();
};
}  // namespace EngineCore