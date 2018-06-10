#include "Camera.h"

#include <assert.h>
#include <iostream>

#include "Settings.h"
#include "Entity.h"
#include "sfmath.h"

sf::RenderWindow* Camera::window = nullptr;
sf::CircleShape Camera::panBoundsCircle;
Entity* Camera::followEntity;

void Camera::init(sf::RenderWindow *window)
{
    Camera::window = window;
    panBoundsCircle.setFillColor(sf::Color::Transparent);
    panBoundsCircle.setOutlineColor(sf::Color(120,120,0,190));
    panBoundsCircle.setOutlineThickness(-1);   
}

void Camera::update(float dt)
{
    auto settings = &Settings::instance();
    panBoundsCircle.setRadius(settings->cameraPanRadius);
    panBoundsCircle.setOrigin(settings->cameraPanRadius, settings->cameraPanRadius);
    panBoundsCircle.setPosition(window->getView().getCenter() + settings->cameraPanOffset);

    if (followEntity)
    {
        auto cPos = panBoundsCircle.getPosition();
        auto ePos = followEntity->getPosition();

        float distanceFromBoundsCenter = distance(cPos, ePos);
        auto vectorFromCameraCenter = ePos - cPos;

        if (distanceFromBoundsCenter > settings->cameraPanRadius)
        {
            auto currentCenterView = window->getView();
            currentCenterView.move((distanceFromBoundsCenter - settings->cameraPanRadius) * normalize(vectorFromCameraCenter));
            auto updatedCenter = currentCenterView.getCenter();
            // TODO: This should be adjusted to be more smooth somehow.
            currentCenterView.setCenter(sf::Vector2f(std::floor(updatedCenter.x*10)/10, std::floor(updatedCenter.y*10)/10));
            window->setView(currentCenterView);
        }
    }
}

void Camera::resetZoom()
{
    auto currentCenterView = window->getView();
    auto defaultView = window->getDefaultView();

    defaultView.zoom(0.25);
    defaultView.setSize(defaultView.getSize().x, defaultView.getSize().y * -1);
    defaultView.setCenter(currentCenterView.getCenter());
    window->setView(defaultView);
}

void Camera::setFollowEntity(Entity* e)
{
    followEntity = e;
}

void Camera::centerOn(Entity *t)
{
    auto currentCenterView = window->getView();
    currentCenterView.setCenter(t->getPosition());
    window->setView(currentCenterView);
}

void Camera::setCenter(sf::Vector2f center)
{
    auto current = window->getView();
    current.setCenter(center);
    window->setView(current);
}

sf::Vector2f Camera::getCenter()
{
    return window->getView().getCenter();
}

sf::Vector2f Camera::getMousePositionInWorld()
{
    return window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}

void Camera::drawBoundsRegion()
{
    assert(window != 0);

    window->draw(panBoundsCircle);
}