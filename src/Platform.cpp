#include "Platform.h"
#include "Animation.h"
#include "Entities.h"
#include "Switch.h"
#include "Camera.h"
#include "util/parsing.h"
#include "sfmath.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

Platform::Platform(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params), currentWaypoint(0), isAtWaypoint(true), isWaypointDirectionAscending(true), moveSwitchesRequired(0)
{

}

Platform::~Platform()
{

}


void Platform::initParameters(std::vector<std::string> params)
{
    Entity::initParameters(params);

    for (auto it : params)
    {
        auto key = it.substr(0, it.find(" "));
        auto value = it.substr(it.find(" ") + 1);

        if (key == "speed") speed = std::stof(value);
        else if (key == "pauseTime") waypointPauseTime = std::stof(value);
        else if (key == "relativeWaypoint")
        {
            auto floats = parse_floats(value);
            sf::Vector2f absoluteWaypoint = getPosition() + sf::Vector2f(floats[0], floats[1]);
            waypoints.push_back(absoluteWaypoint);
        }
        else if (key == "moveSwitchesRequired") moveSwitchesRequired = std::stoi(value);
        else if (key == "moveSwitches")
        {
            auto switches = parse_ints(value);
            
            for (auto id : switches)
            {
                moveSwitches.push_back((Switch*) Entities::getById(id));
            }   
        }
    }

    setPosition(waypoints[0]);
}

EntityType Platform::getEntityType()
{
    return ET_PLATFORM;
}

std::string Platform::getEntityDescription()
{
    std::string relativeWaypointParams = "";
    std::string moveSwitchParams = "";

    auto position = waypoints[0];

    for (auto it : waypoints) 
    {
        relativeWaypointParams += writeParameter("relativeWaypoint", std::to_string(it.x - position.x) + " " + std::to_string(it.y - position.y)); 
    }

    if (moveSwitchesRequired > 0)
    {
        std::string moveIds = "";
        moveSwitchParams += writeParameter("moveSwitchesRequired", moveSwitchesRequired);

        for (auto it : moveSwitches)
        {
            moveIds += std::to_string(it->getId()) + " ";
        }

        moveSwitchParams += writeParameter("moveSwitches", moveIds);
    }

    return std::to_string(id) + " Platform " + name + "\n"
        + writeParameter("position", std::to_string(position.x) + " " + std::to_string(position.y))
        + writeParameter("texture", "world_entities.png")
        + writeParameter("animation", currentAnimation->getName())
        + writeParameter("pauseTime", waypointPauseTime)
        + writeParameter("speed", speed)
        + relativeWaypointParams
        + moveSwitchParams;
}

void Platform::update(float dt)
{
    Entity::update(dt);

    // No motion required
    if (waypoints.size() == 1) return;

    
    if (moveSwitchesRequired > 0)
    {
        int moveSwitchesActive = 0;

        for (auto it : moveSwitches)
        {
            if (it->isPressed())
            {
                moveSwitchesActive++;
            }
        }

        if (moveSwitchesActive < moveSwitchesRequired)
        {
            velocity.x = 0;
            velocity.y = 0;
            return;
        }   
    }

    // Check if we should move to next waypoint and figure out what that should be
    if (isAtWaypoint)
    {
        timeAtCurrentWaypoint += dt;

        if (timeAtCurrentWaypoint >= waypointPauseTime)
        {
            isAtWaypoint = false;

            if (isWaypointDirectionAscending)
            {
                currentWaypoint++;
                if (currentWaypoint == waypoints.size() - 1)
                {
                    isWaypointDirectionAscending = false;
                }
            }
            else
            {
                currentWaypoint--;
                if (currentWaypoint == 0)
                {
                    isWaypointDirectionAscending = true;
                }
            }
        }
    }
    // Move along waypoint line and see if we've reached the next waypoint
    else
    {
        int waypointBIndex = isWaypointDirectionAscending ? currentWaypoint + 1 : currentWaypoint - 1;
        auto waypointA = waypoints[currentWaypoint];
        auto waypointB = waypoints[waypointBIndex];

        auto motionVector = normalize(waypointB - waypointA);

        velocity = speed * motionVector;

        if (distance(getPosition(), waypointA) >= distance(waypointB, waypointA))
        {
            setPosition(waypointB);
            isAtWaypoint = true;
            timeAtCurrentWaypoint = 0;
            velocity = sf::Vector2f(0,0);
        }
    }
}

void Platform::handleEntityCollision(Entity *other)
{
    switch (other->getEntityType())
    {
    case ET_PLAYER:
        break;
    default:
        break;
    }
}

void Platform::drawInspectorWidgets()
{
    static int selectedWaypoint;

    Entity::drawInspectorWidgets();
    
    // TODO: Draw them in the world.
    ImGui::Text("Waypoints");
    ImGui::ListBoxHeader("");
    int currentWaypointIndex = 0;
    for (auto wp : waypoints)
    {
        if (ImGui::Selectable((std::to_string(wp.x) + ", " + std::to_string(wp.y)).c_str(), selectedWaypoint == currentWaypointIndex))
        {
            selectedWaypoint = currentWaypointIndex;
        }
        currentWaypointIndex++; 
    }
    ImGui::ListBoxFooter();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt))
    {
        waypoints[selectedWaypoint] = Camera::getMousePositionInWorld();   
    }

    if (ImGui::Button("Add"))
    {
        waypoints.push_back(sf::Vector2f(0,0));
    }
    ImGui::SameLine();
    if (ImGui::Button("Remove Selected"))
    {
        waypoints.erase(waypoints.begin() + selectedWaypoint);
    }
}