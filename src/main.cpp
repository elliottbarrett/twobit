#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include <iostream>

#include "AnimatedSprite.h"

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

    std::cout << "Hello twobit!" << std::endl;

    AnimatedSprite testSprite;
    testSprite.setTexture(&pokemonTexture);
    testSprite.setScale(WINDOW_SCALE, WINDOW_SCALE);

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time frameTime = frameTimeClock.restart();
        float dt = frameTime.asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased)
                window.close();
        }

        testSprite.update(dt);

        window.clear();
        window.draw(testSprite);
        window.display();
    }

    return 0;
}