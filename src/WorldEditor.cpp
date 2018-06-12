#include <SFML/Graphics.hpp>

#include "WorldEditor.h"
#include "Settings.h"
#include "TileMap.h"
#include "Camera.h"
#include "Entities.h"
#include "Entity.h"
#include "Switch.h"
#include "Door.h"
#include "Platform.h"

#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"
#include <iostream>

WorldEditor::WorldEditor(sf::RenderWindow *worldWindow, TileMap *world)
    : worldWindow(worldWindow), 
      paletteSelectionHighlight(sf::Vector2f(16, 16)),
      world(world),
      paletteTileNumber(0),
      isPainting(false),
      isPanning(false),
      isActive(true),
      selectedEntityId(0)
{
    paletteTexture.loadFromFile("assets/LevelTileset.png");
    paletteSize = paletteTexture.getSize();

    instantiateEditorWindows();
}

void WorldEditor::instantiateEditorWindows()
{
    // Tile Palette
    paletteWindow = new sf::RenderWindow(sf::VideoMode(paletteSize.x * 2, paletteSize.y * 2), "Tile Palette");
    paletteSprite.setTexture(paletteTexture);

    paletteWindow->setSize(sf::Vector2u(2 * paletteSize.x, 2 * paletteSize.y));
    paletteWindow->setPosition(sf::Vector2i(1200, 0));
    paletteWindow->setVerticalSyncEnabled(true);

    paletteSelectionHighlight.setFillColor(sf::Color::Transparent);
    paletteSelectionHighlight.setOutlineThickness(1);
    paletteSelectionHighlight.setOutlineColor(sf::Color(250, 150, 100));

    paletteView = paletteWindow->getDefaultView();
    paletteView.setCenter(paletteSize.x / 2, paletteSize.y / 2);
    paletteView.zoom(0.5);
    paletteWindow->setView(paletteView);

    // Inspector window
    inspectorWindow = new sf::RenderWindow(sf::VideoMode(650, 600), "World Editor");
    inspectorWindow->setPosition(sf::Vector2i(1200, 400));
    inspectorWindow->setVerticalSyncEnabled(true);

    ImGui::SFML::Init(*inspectorWindow);
}

void WorldEditor::handleWorldEvent(sf::Event &event)
{
    sf::Vector2f mousePositionInWorld = Camera::getMousePositionInWorld();

    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::E)
        {
            toggleEditorVisibility();
        }
        else if (event.key.code == sf::Keyboard::C)
        {
            Settings::drawEntityCollisionBounds = !Settings::drawEntityCollisionBounds;
        }
        else if (event.key.code == sf::Keyboard::Space)
        {
            Settings::runGame = !Settings::runGame;
        }
    }

    // Handle other event types differently
    if (isActive == false)
    {
        return;
    }

    if (event.type == sf::Event::MouseButtonPressed)
    {
        int worldX = (int) mousePositionInWorld.x;
        int worldY = (int) mousePositionInWorld.y;
        int tileX = worldX / 16;
        int tileY = worldY / 16;


        if (event.mouseButton.button == sf::Mouse::Left)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && selectedEntityId != 0)
            {
                Entities::getById(selectedEntityId)->setPosition(mousePositionInWorld);
            }
            else if (Settings::smartPaint)
            {
                world->smartPaint(tileX, tileY, paletteTileNumber != 0, SmartPaintConfig::getDefault());
            }
            else
            {
                world->setTile(tileX, tileY, paletteTileNumber);
            }
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
        int tileX = ((int) worldX) / 16;
        int tileY = ((int) worldY) / 16;

        if (isPainting)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) && selectedEntityId != 0)
            {
                Entities::getById(selectedEntityId)->setPosition(mousePositionInWorld);
            }
            else if (Settings::smartPaint)
            {
                world->smartPaint(tileX, tileY, paletteTileNumber != 0, SmartPaintConfig::getDefault());
            }
            else
            {
                world->setTile(tileX, tileY, paletteTileNumber);
            }
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

void WorldEditor::toggleEditorVisibility()
{
    if (isActive)
    {
        paletteWindow->close();
        delete paletteWindow;
        inspectorWindow->close();
        delete inspectorWindow; 
    }
    else
    {
        instantiateEditorWindows();
    }

    isActive = !isActive;
}

void WorldEditor::update(float dt)
{
    if (isActive == false)
    {
        return;
    }

    sf::Event event;

    ImGui::SFML::Update(*inspectorWindow, sf::seconds(dt));

    while (paletteWindow->pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            paletteWindow->close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            sf::Vector2f mousePositionInPalette = paletteWindow->mapPixelToCoords(sf::Mouse::getPosition(*paletteWindow));
            int paletteX = (int) mousePositionInPalette.x;
            int paletteY = (int) mousePositionInPalette.y;

            int tileX = paletteX / 16;
            int tileY = paletteY / 16;

            paletteSelectionHighlight.setPosition(16 * tileX, 16 * tileY);
            paletteTileNumber = (tileY * (paletteSize.x / 16)) + tileX;
        }
        else if (event.type == sf::Event::KeyReleased)
        {
            if (event.key.code == sf::Keyboard::E)
            {
                toggleEditorVisibility();

                if (!isActive)
                {
                    return;
                }
            }      
        }
    }

    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
    {
        sf::Vector2f mousePositionInWorld = worldWindow->mapPixelToCoords(sf::Mouse::getPosition(*worldWindow));
        
        if (isPanning == false)
        {
            isPanning = true;
            Camera::setFollowEntity(nullptr);
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

    // ImGui window event loop
    while (inspectorWindow->pollEvent(event))
    {
        ImGui::SFML::ProcessEvent(event);
    }
}

void WorldEditor::render()
{
    if (isActive == false)
    {
        return;
    }
    paletteWindow->clear();
    paletteWindow->draw(paletteSprite);
    paletteWindow->draw(paletteSelectionHighlight);
    paletteWindow->display();

    auto mousePositionInWindow = sf::Mouse::getPosition(*worldWindow);
    auto mousePositionInWorld = Camera::getMousePositionInWorld();

    inspectorWindow->clear();

    // Global Settings window
    ImGui::SetNextWindowSize(sf::Vector2i(0,0));
    ImGui::Begin("Global Settings");
    ImGui::Checkbox("Run Simulation", &Settings::runGame);
    ImGui::SliderFloat("Time Scale", &Settings::timeScale, 0.1, 2);
    ImGui::Checkbox("Use Grain Shader", &Settings::useGrainShader);
    ImGui::Checkbox("Smart Tile Paint", &Settings::smartPaint);
    ImGui::Checkbox("Draw Entity Collision Bounds", &Settings::drawEntityCollisionBounds);
    ImGui::Checkbox("Draw UI Layer", &Settings::drawUI);
    ImGui::End();

    // Camera window
    ImGui::SetNextWindowSize(sf::Vector2i(0,0));
    ImGui::Begin("Camera");
    if (ImGui::Button("Reset Zoom"))
    {
        Camera::resetZoom();
    }
    if (ImGui::Button("Center on Player"))
    {
        Camera::centerOn(Entities::getByName("Player1"));
    }
    float cameraCenterX = Camera::getCenter().x;
    float cameraCenterY = Camera::getCenter().y;
    float cameraCenterTemp[2] = {cameraCenterX, cameraCenterY};
    if (ImGui::DragFloat2("Center", cameraCenterTemp))
    {
        Camera::setCenter(sf::Vector2f(cameraCenterTemp[0], cameraCenterTemp[1]));
    }
    ImGui::Checkbox("Draw Pan Bounds", &Settings::drawCameraPanRegion);
    ImGui::SliderFloat("Circle Pan Radius", &Settings::cameraPanRadius, 0, 80);
    float currentPanOffset[2] = { Settings::cameraPanOffset.x, Settings::cameraPanOffset.y };
    ImGui::DragFloat2("Pan Bounds Offset", currentPanOffset);
    Settings::cameraPanOffset = sf::Vector2f(currentPanOffset[0], currentPanOffset[1]);
    ImGui::End();

    // Physics window
    ImGui::SetNextWindowSize(sf::Vector2i(0,0));
    ImGui::Begin("Physics");
    ImGui::SliderFloat("Gravity", &Settings::gravity, -1000, 0);
    ImGui::SliderFloat("Jump Speed", &Settings::jumpSpeed, 0, 400);
    ImGui::SliderFloat("Walk Speed", &Settings::walkSpeed, 0, 125);
    ImGui::End();

    // Entities window
    ImGui::SetNextWindowSize(sf::Vector2i(0,0));
    ImGui::Begin("Entities");
    if (ImGui::BeginMenuBar())
    {
        bool testMenuItem;
        if (ImGui::BeginMenu("Add"))
        {
            ImGui::MenuItem("Player", NULL, &testMenuItem);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
        ImGui::Spacing();
    }
    ImGui::Text("Entity count: %d", Entities::getCount());
    ImGui::ListBoxHeader("Entities", Entities::getCount());
    for (auto entity : Entities::getEntities())
    {
        if (ImGui::Selectable(entity->getName().c_str(), selectedEntityId == entity->getId()))
        {
            selectedEntityId = entity->getId();
            Camera::centerOn(entity);
            Camera::setFollowEntity(entity);
        }
    }
    ImGui::ListBoxFooter();
    if (ImGui::Button("Save File"))
    {
        Entities::writeFile("assets/entities.tbe");
    }
    ImGui::End();    
    
    // Entity Inspector window
    if (selectedEntityId != 0)
    {
        auto selectedEntity = Entities::getById(selectedEntityId);
        ImGui::SetNextWindowSize(sf::Vector2i(0,0));
        ImGui::Begin("Entity Inspector");
        selectedEntity->drawInspectorWidgets();
        ImGui::End();
    }

    // Entity Palette Window
    static int selectedEntityTypeIndex;
    ImGui::SetNextWindowSize(sf::Vector2i(130,0));
    ImGui::Begin("Entity Palette");
    ImGui::ListBoxHeader("");
    if (ImGui::Selectable("Door", selectedEntityTypeIndex == 0))
    {
        selectedEntityTypeIndex = 0;
    }
    if (ImGui::Selectable("Switch", selectedEntityTypeIndex == 1))
    {
        selectedEntityTypeIndex = 1;
    }
    if (ImGui::Selectable("Platform", selectedEntityTypeIndex == 2))
    {
        selectedEntityTypeIndex = 2;
    }
    ImGui::ListBoxFooter();
    if (ImGui::Button("Add New"))
    {
        std::vector<std::string> defaultParams;
        auto newEntityId = Entities::getMaxId() + 1;
        auto cameraPositionString = std::to_string(Camera::getCenter().x) + " " + std::to_string(Camera::getCenter().y);

        defaultParams.push_back("position " + cameraPositionString);

        switch (selectedEntityTypeIndex)
        {
        case 0:
            defaultParams.push_back("texture world_entities.png");
            defaultParams.push_back("animation door_closed");
            new Door(newEntityId, "NewDoor", defaultParams);
            break;
        case 1:
            defaultParams.push_back("texture world_entities.png");
            defaultParams.push_back("animation floor_switch_inactive");
            defaultParams.push_back("type floor");
            new Switch(newEntityId, "NewSwitch", defaultParams);
            break;
        case 2:
            defaultParams.push_back("texture world_entities.png");
            defaultParams.push_back("animation platform_1");
            defaultParams.push_back("speed 40");
            defaultParams.push_back("pauseTime 0.5");
            defaultParams.push_back("waypoint " + cameraPositionString);
            new Platform(newEntityId, "NewPlatform", defaultParams);
            break;
        }
    }
    ImGui::End();

    ImGui::SetNextWindowSize(sf::Vector2i(0,0));
    ImGui::Begin("Mouse Info");
    ImGui::Text("Window position: (%d, %d)", mousePositionInWindow.x, mousePositionInWindow.y);
    ImGui::Text("World position: (%f, %f)", mousePositionInWorld.x, mousePositionInWorld.y);
    ImGui::End();

    ImGui::SFML::Render(*inspectorWindow);
    inspectorWindow->display();
}

WorldEditor::~WorldEditor()
{
    delete paletteWindow;
    delete inspectorWindow;
}