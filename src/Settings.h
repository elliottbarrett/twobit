#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

class Settings
{
public:
    bool useGrainShader;
    bool renderTilemapCollisions;
    bool drawCameraPanRect;
    bool drawEntityOrigins;
    bool drawEntityCollisionBounds;
    float cameraPanWidth;
    float cameraPanHeight;
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
        useGrainShader(true),
        renderTilemapCollisions(true),
        drawEntityOrigins(false),
        drawEntityCollisionBounds(true),
        drawCameraPanRect(false),
        cameraPanWidth(100),
        cameraPanHeight(100),
        gravity(-750),
        jumpSpeed(250),
        walkSpeed(80)
    {
    }

public:
    Settings(Settings const&) = delete;
    void operator=(Settings const&)  = delete;
};

#endif