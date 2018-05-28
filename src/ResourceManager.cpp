#include "ResourceManager.h"

std::map<std::string, sf::Texture*> ResourceManager::textures = std::map<std::string, sf::Texture*>();
std::map<std::string, Animation*> ResourceManager::animations = std::map<std::string, Animation*>();

sf::Texture* ResourceManager::getTexture(std::string name)
{
    // TODO --- deal with file not found case.
    if (textures.find(name) == textures.end())
    {
        auto newTexture = new sf::Texture();
        newTexture->loadFromFile("assets/" + name);
        textures[name] = newTexture;
    }

    return textures[name];
}

Animation* ResourceManager::getAnimation(std::string name)
{
    if (animations.find(name) == animations.end())
    {
        return nullptr;
    }
    return animations[name];
}