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

#define GB_WIDTH 160
#define GB_HEIGHT 144
#define WINDOW_SCALE 4

int main()
{
    sf::RenderWindow window(sf::VideoMode(GB_WIDTH * WINDOW_SCALE, GB_HEIGHT * WINDOW_SCALE), "SFML works!");
    sf::Clock frameTimeClock;
    window.setVerticalSyncEnabled(true);

    sf::Texture pokemonTexture;
    pokemonTexture.loadFromFile("assets/pokemon.png");
    auto pokemonSprite = sf::Sprite(pokemonTexture);
    pokemonSprite.setScale(WINDOW_SCALE, WINDOW_SCALE);

    AnimatedSprite testSprite;
    testSprite.setTexture(&pokemonTexture);
    testSprite.setScale(WINDOW_SCALE, WINDOW_SCALE);

    GameContext* ctx = new TitleContext();

    // Test some TileMap stuff
    TileMap tileMap;
    tileMap.setScale(4, 4);
    
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
                window.close();

            if (ArcadeInput::isWhiteButtonPressed())
            {
                window.close();
            }
        }

        testSprite.update(dt);
        ctx->update(dt);

        window.clear();
        // ctx->render(window);
        // window.draw(testSprite);
        window.draw(tileMap);
        window.display();
    }

    return 0;
}