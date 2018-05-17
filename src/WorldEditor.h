#ifndef WORLDEDITOR_H_INCLUDED
#define WORLDEDITOR_H_INCLUDED

#include <SFML/Graphics.hpp>

class TileMap;

class WorldEditor
{
public:
    WorldEditor(sf::RenderWindow *worldWindow, TileMap *world);
    ~WorldEditor();

    void update(float dt);
    void render();
    void handleWorldEvent(sf::Event &event);

private:
    void instantiateEditorWindows();
    void toggleEditorVisibility();

    sf::RenderWindow* worldWindow;
    sf::RenderWindow* paletteWindow;
    sf::Texture paletteTexture;
    sf::Sprite paletteSprite;
    sf::View paletteView;
    sf::Vector2u paletteSize;
    sf::RectangleShape paletteSelectionHighlight;
    TileMap* world;
    int paletteTileNumber;
    bool isPainting;
    bool isPanning;
    bool isActive;
    sf::Vector2f panWorldCoordinatesLastFrame;

    // ImGui stuff
    sf::RenderWindow* inspectorWindow;
    unsigned int selectedEntityId;

};

#endif