#include "AnimatedSprite.h"
#include "GameContext.h"
#include "TitleContext.h"
#include "ArcadeInput.h"
#include "TileMap.h"
#include "Player.h"
#include "Settings.h"
#include "WorldEditor.h"
#include "Camera.h"
#include "Entities.h"
#include "UI.h"
#include "ResourceManager.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <math.h>
#include <stdlib.h>

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

#define GB_WIDTH 256
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

    Camera::init(&window);

    if (!grainShader.loadFromFile("shaders/grain.frag", sf::Shader::Type::Fragment))
    {
        std::cout << "Shader loading failed!" << std::endl;
        return -1;
    }

    // Test some TileMap stuff
    TileMap tileMap;

    // Test entity system
    ResourceManager::loadAnimationFile("assets/player.anim");
    ResourceManager::loadAnimationFile("assets/door.anim");
    ResourceManager::loadAnimationFile("assets/switch.anim");
    ResourceManager::loadAnimationFile("assets/poordog.anim");
    ResourceManager::loadAnimationFile("assets/platform.anim");
    Entities::loadFromFile("assets/entities.tbe");

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

    Player* player = (Player*) Entities::getByName("Player1");

    if (!tileMap.load())
    {
        std::cout << "TileMap load failed" << std::endl;
        return -1;
    }

    Camera::setFollowEntity(player);

    UI::init(window);

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time frameTime = frameTimeClock.restart();
        float dt = frameTime.asSeconds() * settings->timeScale;

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
            else if (event.type == sf::Event::Resized)
            {
                auto newWidth = event.size.width;
                auto newHeight = event.size.height;

                grainTexture.create(newWidth, newHeight);

                UI::handleResize(newWidth, newHeight);
            }

            worldEditor.handleWorldEvent(event);
        }
        
        if (ArcadeInput::isWhiteButtonPressed())
        {
            window.close();
        }

        if (settings->runGame)
        {
            Entities::update(dt, tileMap);
            // Entities::handleEntityCollisions();
        }

        Camera::update(dt);
        window.clear(sf::Color(155,154,155));
        // ctx->render(window);

        window.draw(tileMap);
        Entities::draw(window);

        if (settings->drawUI)
        {
            UI::draw(window);
        }

        // window.draw(testMessageBox);

        if (settings->drawCameraPanRegion)
        {
            Camera::drawBoundsRegion();
        }

        if (settings->useGrainShader)
        {
            grainTexture.update(window);
            sf::View currentView = window.getView();
            window.setView(window.getDefaultView());
            window.clear(sf::Color::Black);
            window.draw(grainSprite, &grainShader);
            window.setView(currentView);
        }

        window.display();

        worldEditor.update(dt);
        worldEditor.render();
    }

    tileMap.save();
    return 0;

}
