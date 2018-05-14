#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "AnimatedSprite.h"
#include "GameContext.h"
#include "TitleContext.h"
#include "ArcadeInput.h"
#include "TileMap.h"
#include "Player.h"
#include "Settings.h"
#include "WorldEditor.h"
#include "imgui.h"
#include "imgui-SFML.h"

#define GB_WIDTH 160
#define GB_HEIGHT 144
#define WINDOW_SCALE 4

int main()
{
    // Init settings
    auto settings = &Settings::instance();
    
    // Main window
    sf::RenderWindow window(sf::VideoMode(GB_WIDTH * WINDOW_SCALE, GB_HEIGHT * WINDOW_SCALE), "twobit");
    window.setVerticalSyncEnabled(true);

    sf::Shader grainShader;
    sf::Texture grainTexture;
    sf::Sprite grainSprite;
    grainTexture.create(GB_WIDTH * WINDOW_SCALE, GB_HEIGHT * WINDOW_SCALE);
    grainSprite.setTexture(grainTexture);

    if (!grainShader.loadFromFile("shaders/grain.frag", sf::Shader::Type::Fragment))
    {
        std::cout << "Shader loading failed!" << std::endl;
        return -1;
    }

    // Test some TileMap stuff
    TileMap tileMap;

    // Editor window
    WorldEditor worldEditor(&window, &tileMap);

    // Timer / frame management
    sf::Clock frameTimeClock;
    sf::Clock elapsedTimeClock;
    unsigned int frameCount = 0;

    elapsedTimeClock.restart();

    // Fixing the fucking coordinate system...
    sf::View yIsUpView = window.getDefaultView();
    yIsUpView.setSize(yIsUpView.getSize().x, yIsUpView.getSize().y * -1);
    yIsUpView.zoom(0.25);
    yIsUpView.setCenter(GB_WIDTH/2, GB_HEIGHT/2);
    window.setView(yIsUpView);

    Player player(1);
    sf::Texture pokemonTexture;
    pokemonTexture.loadFromFile("assets/pokemon.png");
    player.setTexture(&pokemonTexture);

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

        // Update shader params
        grainShader.setUniform("time", elapsedTimeClock.getElapsedTime().asSeconds());

        // Event loop
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

        player.update(dt);
        ctx->update(dt);


        player.handleWorldCollision(tileMap.checkWorldCollisions(player.getCollisionBounds()));

        window.clear();
        // ctx->render(window);

        window.draw(tileMap);
        window.draw(player);

        if (settings->useGrainShader)
        {
            grainTexture.update(window);
            sf::View currentView = window.getView();
            window.setView(window.getDefaultView());
            window.draw(grainSprite, &grainShader);
            window.setView(currentView);
        }


        // // ImGui testing
        // ImGui::SFML::Update(window, frameTime);

        // ImGui::Begin("Sample window");

        // if (ImGui::Button("Test button"))
        // {
        //     std::cout << "test button clicked" << std::endl;            
        // }

        // ImGui::End();
        // ImGui::SFML::Render(window);
        // END ImGui testing

        window.display();

        worldEditor.update(dt);
        worldEditor.render();
    }

    tileMap.save();
    return 0;
}