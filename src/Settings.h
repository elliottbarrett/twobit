#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

class Settings
{
public:
    bool runGame;
    bool useGrainShader;
    bool renderTilemapCollisions;
    bool drawCameraPanRegion;
    bool drawEntityOrigins;
    bool drawEntityCollisionBounds;
    float cameraPanRadius;
    sf::Vector2f cameraPanOffset;
    float gravity;
    float jumpSpeed;
    float walkSpeed;

    static Settings& instance()
    {
        static Settings instance;
        return instance;
    }

private:
    Settings() :
        runGame(true),
        useGrainShader(true),
        renderTilemapCollisions(true),
        drawCameraPanRegion(false),
        drawEntityOrigins(false),
        drawEntityCollisionBounds(true),
        cameraPanRadius(40),
        cameraPanOffset(sf::Vector2f(0,0)),
        gravity(-750),
        jumpSpeed(250),
        walkSpeed(80)
    {
    }

    // TODO
    // void loadSettingsFile();

public:
    Settings(Settings const&) = delete;
    void operator=(Settings const&)  = delete;
};

#endif