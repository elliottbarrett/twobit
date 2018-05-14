#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

class Settings
{
public:
    bool useGrainShader;
    bool renderTilemapCollisions;

    static Settings& instance()
    {
        static Settings instance;

        return instance;
    }

private:
    Settings() :
        useGrainShader(true),
        renderTilemapCollisions(true)
    {

    }

public:
    Settings(Settings const&) = delete;
    void operator=(Settings const&)  = delete;
};

#endif