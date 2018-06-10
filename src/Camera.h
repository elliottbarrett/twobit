#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <SFML/Graphics.hpp>

class Entity;

class Camera
{
public:
    static void init(sf::RenderWindow *window);
    static void update(float dt);
    static void resetZoom();
    static void centerOn(Entity *t);
    static void drawBoundsRegion();
    static void setFollowEntity(Entity* e);
    static sf::Vector2f getCenter();
    static sf::Vector2f getMousePositionInWorld();
    static void setCenter(sf::Vector2f center);

private:
    static sf::RenderWindow *window;
    static sf::CircleShape panBoundsCircle;
    static Entity *followEntity;

public:
    Camera(Camera const&) = delete;
    void operator=(Camera const&)  = delete;
};

#endif