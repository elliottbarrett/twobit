#include "WorldEditor.h"
#include "TileMap.h"

WorldEditor::WorldEditor(sf::RenderWindow *worldWindow, TileMap *world)
    : worldWindow(worldWindow), 
      world(world),
      paletteSelectionHighlight(sf::Vector2f(16, 16)),
      isPainting(false)
{
    paletteTexture.loadFromFile("assets/LevelTileset.png");
    paletteSize = paletteTexture.getSize();
    paletteWindow = new sf::RenderWindow(sf::VideoMode(paletteSize.x * 2, paletteSize.y * 2), "Tile Palette");
    paletteSprite.setTexture(paletteTexture);

    paletteWindow->setSize(sf::Vector2u(2 * paletteSize.x, 2 * paletteSize.y));
    paletteWindow->setPosition(sf::Vector2i(900, 0));
    paletteWindow->setVerticalSyncEnabled(true);

    paletteSelectionHighlight.setFillColor(sf::Color::Transparent);
    paletteSelectionHighlight.setOutlineThickness(1);
    paletteSelectionHighlight.setOutlineColor(sf::Color(250, 150, 100));

    paletteView = paletteWindow->getDefaultView();
    paletteView.setCenter(paletteSize.x / 2, paletteSize.y / 2);
    paletteView.zoom(0.5);
    paletteWindow->setView(paletteView);
}

void WorldEditor::handleWorldEvent(sf::Event &event)
{

    sf::Vector2f mousePositionInWorld = worldWindow->mapPixelToCoords(sf::Mouse::getPosition(*worldWindow));

    if (event.type == sf::Event::MouseButtonPressed)
    {
        int worldX = (int) mousePositionInWorld.x;
        int worldY = (int) mousePositionInWorld.y;
        int tileX = worldX / 16;
        int tileY = worldY / 16;

        if (event.mouseButton.button == sf::Mouse::Left)
        {
            world->setTile(tileX, tileY, paletteTileNumber);
            isPainting = true;
        }
    }
    else if (event.type == sf::Event::MouseButtonReleased)
    {
        // TODO: Fix for the case where someone was both panning and painting
        isPainting = false;
        isPanning = false;
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        float worldX = mousePositionInWorld.x;
        float worldY = mousePositionInWorld.y;

        if (isPainting)
        {
            int tileX = ((int) worldX) / 16;
            int tileY = ((int) worldY) / 16;
            world->setTile(tileX, tileY, paletteTileNumber);
        }
    }
    else if (event.type == sf::Event::MouseWheelMoved)
    {
        // Zoom view
        sf::View zoomingView = worldWindow->getView();
        float zoomFactor = 1.0 + event.mouseWheel.delta * 0.12;
        zoomingView.zoom(zoomFactor);
        worldWindow->setView(zoomingView);
    }
}

void WorldEditor::update()
{ 
    sf::Event event;

    while (paletteWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            paletteWindow->close();
        }

        if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f mousePositionInPalette = paletteWindow->mapPixelToCoords(sf::Mouse::getPosition(*paletteWindow));
            int paletteX = (int) mousePositionInPalette.x;
            int paletteY = (int) mousePositionInPalette.y;

            int tileX = paletteX / 16;
            int tileY = paletteY / 16;

            paletteSelectionHighlight.setPosition(16 * tileX, 16 * tileY);
            paletteTileNumber = (tileY * (paletteSize.x / 16)) + tileX;
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        sf::Vector2f mousePositionInWorld = worldWindow->mapPixelToCoords(sf::Mouse::getPosition(*worldWindow));
        
        if (isPanning == false)
        {
            isPanning = true;
        }
        else
        {
            float panDeltaX = panWorldCoordinatesLastFrame.x - mousePositionInWorld.x;
            float panDeltaY = panWorldCoordinatesLastFrame.y - mousePositionInWorld.y;

            auto currentWorldView = worldWindow->getView();
            currentWorldView.move(panDeltaX, panDeltaY);

            worldWindow->setView(currentWorldView);
        }

        panWorldCoordinatesLastFrame = worldWindow->mapPixelToCoords(sf::Mouse::getPosition(*worldWindow));
    }

}

void WorldEditor::render()
{
    paletteWindow->clear();
    paletteWindow->draw(paletteSprite);
    paletteWindow->draw(paletteSelectionHighlight);
    paletteWindow->display();
}

WorldEditor::~WorldEditor()
{
    delete paletteWindow;
}