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
#include "WorldEditor.h"

#define GB_WIDTH 160
#define GB_HEIGHT 144
#define WINDOW_SCALE 4

int main()
{
    // Main window
    sf::RenderWindow window(sf::VideoMode(GB_WIDTH * WINDOW_SCALE, GB_HEIGHT * WINDOW_SCALE), "twobit");
    window.setVerticalSyncEnabled(true);

    // Test some TileMap stuff
    TileMap tileMap;

    // Editor window
    WorldEditor worldEditor(&window, &tileMap);

    // Timer / frame management
    sf::Clock frameTimeClock;
    unsigned int frameCount = 0;

    // Fixing the fucking coordinate system...
    sf::View yIsUpView = window.getDefaultView();
    yIsUpView.setSize(yIsUpView.getSize().x, yIsUpView.getSize().y * -1);
    yIsUpView.zoom(0.25);
    yIsUpView.setCenter(GB_WIDTH/2, GB_HEIGHT/2);
    window.setView(yIsUpView);

    Player testSprite;
    sf::Texture pokemonTexture;
    pokemonTexture.loadFromFile("assets/pokemon.png");
    testSprite.setTexture(&pokemonTexture);

    GameContext* ctx = new TitleContext();


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

        frameCount++;

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }

            worldEditor.handleWorldEvent(event);
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

        worldEditor.update();
        worldEditor.render();
    }

    tileMap.save();
    return 0;
}