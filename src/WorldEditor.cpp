#include <SFML/Graphics.hpp>

#include "WorldEditor.h"
#include "Settings.h"
#include "TileMap.h"
#include "Camera.h"
#include "Entities.h"
#include "Entity.h"

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
    paletteWindow->setPosition(sf::Vector2i(900, 0));
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
    inspectorWindow->setPosition(sf::Vector2i(900, 400));
    inspectorWindow->setVerticalSyncEnabled(true);

    ImGui::SFML::Init(*inspectorWindow);
}

void WorldEditor::handleWorldEvent(sf::Event &event)
{
    sf::Vector2f mousePositionInWorld = worldWindow->mapPixelToCoords(sf::Mouse::getPosition(*worldWindow));

    if (event.type == sf::Event::KeyReleased)
    {
        if (event.key.code == sf::Keyboard::E)
        {
            toggleEditorVisibility();
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
            world->smartPaint(tileX, tileY, paletteTileNumber != 0, SmartPaintConfig::getDefault());
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
            world->smartPaint(tileX, tileY, paletteTileNumber != 0, SmartPaintConfig::getDefault());
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
            Camera::instance().setFollowEntity(nullptr);
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

    auto settings = &Settings::instance();

    inspectorWindow->clear();

    // Global Settings window
    ImGui::SetNextWindowSize(sf::Vector2i(0,0));
    ImGui::Begin("Global Settings");
    ImGui::Checkbox("Run Simulation", &settings->runGame);
    ImGui::Checkbox("Use Grain Shader", &settings->useGrainShader);
    ImGui::Checkbox("Draw TileMap Collisions", &settings->renderTilemapCollisions);
    ImGui::Checkbox("Draw Entity Collision Bounds", &settings->drawEntityCollisionBounds);
    ImGui::End();

    // Camera window
    ImGui::SetNextWindowSize(sf::Vector2i(0,0));
    ImGui::Begin("Camera");
    if (ImGui::Button("Reset Zoom"))
    {
        Camera::instance().resetZoom();
    }
    if (ImGui::Button("Center on Player"))
    {
        Camera::instance().centerOn(Entities::getByName("Player1"));
    }
    ImGui::Checkbox("Draw Pan Bounds", &settings->drawCameraPanRegion);
    ImGui::SliderFloat("Circle Pan Radius", &settings->cameraPanRadius, 0, 80);
    float currentPanOffset[2] = { settings->cameraPanOffset.x, settings->cameraPanOffset.y };
    ImGui::DragFloat2("Pan Bounds Offset", currentPanOffset);
    settings->cameraPanOffset = sf::Vector2f(currentPanOffset[0], currentPanOffset[1]);
    ImGui::End();

    // Physics window
    ImGui::SetNextWindowSize(sf::Vector2i(0,0));
    ImGui::Begin("Physics");
    ImGui::SliderFloat("Gravity", &settings->gravity, -1000, 0);
    ImGui::SliderFloat("Jump Speed", &settings->jumpSpeed, 0, 400);
    ImGui::SliderFloat("Walk Speed", &settings->walkSpeed, 0, 125);
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
            Camera::instance().centerOn(entity);
            Camera::instance().setFollowEntity(entity);
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

    // Sprite editor
    ImGui::SetNextWindowSize(sf::Vector2i(0,0));
    ImGui::Begin("Sprite Editor");

    // ImGui::Columns(2, "SpriteEditor columns", true);
    ImGui::BeginGroup();
    {
        if (ImGui::TreeNode("Category"))
        {
            if (ImGui::TreeNode("Entity"))
            {
                static bool selected = false;
                ImGui::Selectable("Selectable", &selected);

                ImGui::TreePop();
            }

            ImGui::TreePop();
        }
    }
    ImGui::EndGroup(); 
    // ImGui::Separator();
    ImGui::SameLine(); ImGui::BeginGroup();
    {
        ImGui::Text("Right of tree");
        ImGui::Text("Stuff goes here");
        ImGui::Text("Hopefully the editor panel");
        ImGui::Text("Where we can edit frame data");
        ImGui::Text("And collision info too!");
    }
    ImGui::EndGroup();
    
    if (ImGui::Button("Save File"))
    {
        // todo
        std::cout << "saving..\n";
    }
    ImGui::End();

    ImGui::SFML::Render(*inspectorWindow);
    inspectorWindow->display();
}

WorldEditor::~WorldEditor()
{
    delete paletteWindow;
    delete inspectorWindow;
}