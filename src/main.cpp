#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "AnimatedSprite.h"
#include "GameContext.h"
#include "TitleContext.h"
#include "ArcadeInput.h"
#include "TileMap.h"
#include "Player.h"

#define GB_WIDTH 160
#define GB_HEIGHT 144
#define WINDOW_SCALE 4

int main()
{
    // Main window
    sf::RenderWindow window(sf::VideoMode(GB_WIDTH * WINDOW_SCALE, GB_HEIGHT * WINDOW_SCALE), "SFML works!");
    window.setVerticalSyncEnabled(true);

    // Editor code
    sf::Texture paletteTexture;
    sf::Sprite paletteSprite;
    sf::Vector2u paletteSize;
    sf::View paletteView;
    int paletteTileNumber = 0;
    bool editorIsPainting = false;

    paletteTexture.loadFromFile("assets/LevelTileset.png");
    paletteSize = paletteTexture.getSize();
    paletteSprite.setTexture(paletteTexture);

    sf::RectangleShape paletteSelectionHighlight(sf::Vector2f(16,16));
    paletteSelectionHighlight.setFillColor(sf::Color::Transparent);
    paletteSelectionHighlight.setOutlineThickness(1);
    paletteSelectionHighlight.setOutlineColor(sf::Color(250, 150, 100));

    sf::RenderWindow paletteWindow(sf::VideoMode(paletteSize.x * 2, paletteSize.y * 2), "Editor Palette");
    paletteWindow.setSize(sf::Vector2u(2 * paletteSize.x, 2 * paletteSize.y));
    paletteWindow.setView(sf::View(sf::FloatRect(0, 0, (float) paletteTexture.getSize().x, (float) paletteTexture.getSize().y)));
    paletteWindow.setPosition(sf::Vector2i(900, 0));
    paletteWindow.setVerticalSyncEnabled(true);

    paletteView = paletteWindow.getDefaultView();
    paletteView.setCenter(paletteSize.x / 2, paletteSize.y / 2);
    paletteView.zoom(0.5);
    paletteWindow.setView(paletteView);

    // Timer
    sf::Clock frameTimeClock;

    // Fixing the fucking coordinate system...
    sf::View yIsUpView = window.getDefaultView();
    yIsUpView.setSize(yIsUpView.getSize().x, yIsUpView.getSize().y * -1);
    yIsUpView.zoom(0.25);
    yIsUpView.setCenter(GB_WIDTH/2, GB_HEIGHT/2);
    window.setView(yIsUpView);

    sf::Texture pokemonTexture;
    pokemonTexture.loadFromFile("assets/pokemon.png");
    auto pokemonSprite = sf::Sprite(pokemonTexture);
    pokemonSprite.setScale(WINDOW_SCALE, WINDOW_SCALE);

    Player testSprite;
    testSprite.setTexture(&pokemonTexture);

    GameContext* ctx = new TitleContext();

    // Test some TileMap stuff
    TileMap tileMap;

    if (!tileMap.load())
    {
        std::cout << "TileMap load failed" << std::endl;
        return -1;
    }

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time frameTime = frameTimeClock.restart();
        float dt = frameTime.asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

                int worldX = (int) worldPos.x;
                int worldY = (int) worldPos.y;
                int tileX = worldX / 16;
                int tileY = worldY / 16;

                tileMap.setTile(tileX, tileY, paletteTileNumber);
                editorIsPainting = true;
            }
            else if (event.type == sf::Event::MouseMoved && editorIsPainting)
            {
                sf::Vector2f worldPos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
                
                int worldX = (int) worldPos.x;
                int worldY = (int) worldPos.y;
                int tileX = worldX / 16;
                int tileY = worldY / 16;

                tileMap.setTile(tileX, tileY, paletteTileNumber);
            }
            else if (event.type == sf::Event::MouseButtonReleased)
            {
                editorIsPainting = false;
            }
        }

        if (ArcadeInput::isWhiteButtonPressed())
        {
            window.close();
        }

        testSprite.update(dt);
        ctx->update(dt);

        window.clear();
        // ctx->render(window);
        window.draw(tileMap);
        window.draw(testSprite);
        window.display();

        while (paletteWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                paletteWindow.close();

            if (event.type == sf::Event::MouseButtonPressed)
            {
                sf::Vector2f worldPos = paletteWindow.mapPixelToCoords(sf::Mouse::getPosition(paletteWindow));
                int paletteX = (int) worldPos.x;
                int paletteY = (int) worldPos.y;

                int tileX = paletteX / 16;
                int tileY = paletteY / 16;

                paletteSelectionHighlight.setPosition(16 * tileX, 16 * tileY);
                paletteTileNumber = (tileY * (paletteSize.x / 16)) + tileX;
            }
        }

        paletteWindow.clear();
        paletteWindow.draw(paletteSprite);
        paletteWindow.draw(paletteSelectionHighlight);
        paletteWindow.display();
    }

    tileMap.save();
    return 0;
}