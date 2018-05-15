#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <SFML/Graphics.hpp>

class Camera
{
public:
    static Camera& instance()
    {
        static Camera instance;
        return instance;
    }

    void init(sf::RenderWindow *window);
    void update(float dt);
    void resetZoom();
    void centerOn(sf::Transformable &t);

private:
    Camera() {}
    sf::RenderWindow *window;

public:
    Camera(Camera const&) = delete;
    void operator=(Camera const&)  = delete;
};

#endif