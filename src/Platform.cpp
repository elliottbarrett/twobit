#include "Platform.h"
#include "Animation.h"
#include "util/parsing.h"
#include "sfmath.h"
#include "imgui/imgui.h"
#include "imgui/imgui-SFML.h"

Platform::Platform(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params), currentWaypoint(0), isAtWaypoint(true), isWaypointDirectionAscending(true)
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
        else if (key == "waypoint")
        {
            auto floats = parse_floats(value);
            waypoints.push_back(sf::Vector2f(floats[0], floats[1]));
        }
    }
}

EntityType Platform::getEntityType()
{
    return ET_PLATFORM;
}

std::string Platform::getEntityDescription()
{
    std::string waypointParams = "";

    for (auto it : waypoints) 
    {
        waypointParams += writeParameter("waypoint", std::to_string(it.x) + " " + std::to_string(it.y)); 
    }

    return std::to_string(id) + " Platform " + name + "\n"
        + getCommonParameters()
        + writeParameter("texture", "world_entities.png")
        + writeParameter("animation", currentAnimation->getName())
        + writeParameter("pauseTime", waypointPauseTime)
        + waypointParams;
}

void Platform::update(float dt)
{
    Entity::update(dt);

    // No motion required
    if (waypoints.size() == 1) return;

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
    Entity::drawInspectorWidgets();
    // TODO: Make viewable, addable, editable
    // ImGui::Text("Waypoints");
    // for (auto wp : waypoints)
    // {
    //     float wayPointCoords[2] = {wp.x, wp.y};
    //     ImGui::SliderFloat2    
    // }
}