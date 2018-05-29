#include "ResourceManager.h"
#include "Animation.h"
#include "util/parsing.h"
#include "util/strings.h"

#include <iostream>
#include <fstream>

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

void ResourceManager::loadAnimationFile(std::string fileName)
{
    std::ifstream fileStream(fileName);
    
    std::string line;
    
    auto currentAnimation = new Animation();
    std::string currentName = "";
    std::string currentTexture = "";
    float currentFrameTime = -1;

    while (std::getline(fileStream, line))
    {
        if (line == "END") break;

        if (line == "") // Reach end of frames
        {
            animations[currentName] = currentAnimation;
            currentAnimation = new Animation();
        }
        else if (starts_with(line, "."))
        {
            currentName = line.substr(1);
        }
        else if (starts_with(line, "frameTime"))
        {
            currentFrameTime = std::stof(line.substr(line.find(" ") + 1));
            currentAnimation->setTimePerFrame(currentFrameTime);
        }
        else if (starts_with(line, "origin"))
        {
            auto floats = parse_floats(line.substr(line.find(" ") + 1));
            currentAnimation->setOrigin(sf::Vector2f(floats[0], floats[1]));
        }   
        else
        {
            auto frameInfo = parse_floats(line);
            auto frameBounds = sf::IntRect(frameInfo[0], frameInfo[1], frameInfo[2], frameInfo[3]);
            auto collisionBounds = sf::FloatRect(frameInfo[4], frameInfo[5], frameInfo[6], frameInfo[7]);
            currentAnimation->addFrame(frameBounds, collisionBounds);
        }
    }
}

Animation* ResourceManager::getAnimation(std::string name)
{
    if (animations.find(name) == animations.end())
    {
        std::cout << "ResourceManager: could not find animation " << name << "\n";
        return nullptr;
    }
    return animations[name];
}