#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <map>
#include <string>

class ResourceManager
{
public:
    static sf::Texture* getTexture(std::string name);
private:
    static std::map<std::string, sf::Texture*> textures;
};

#endif