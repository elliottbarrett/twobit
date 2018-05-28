#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class Animation;

class ResourceManager
{
public:
    static sf::Texture* getTexture(std::string name);
    static Animation* getAnimation(std::string name);

    static void loadAnimationFile(std::string fileName);
private:
    static std::map<std::string, sf::Texture*> textures;
    static std::map<std::string, Animation*> animations;
};

#endif