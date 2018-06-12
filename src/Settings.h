#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <SFML/Graphics.hpp>

class Settings
{
public:
    static bool runGame;
    static bool smartPaint;
    static bool useGrainShader;
    static bool drawCameraPanRegion;
    static bool drawEntityOrigins;
    static bool drawEntityCollisionBounds;
    static bool drawUI;
    static float cameraPanRadius;
    static sf::Vector2f cameraPanOffset;
    static float gravity;
    static float jumpSpeed;
    static float walkSpeed;
    static float timeScale;

private:

};

#endif