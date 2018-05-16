#include "Camera.h"

#include <assert.h>
#include <iostream>

#include "Settings.h"
#include "Entity.h"

void Camera::init(sf::RenderWindow *window)
{
    this->window = window;
    panBoundsRect.setFillColor(sf::Color::Transparent);
    panBoundsRect.setOutlineColor(sf::Color(120,0,120,190));
    panBoundsRect.setOutlineThickness(-1);   
}

void Camera::update(float dt)
{
    auto settings = &Settings::instance();
    panBoundsRect.setSize(sf::Vector2f(settings->cameraPanWidth, settings->cameraPanHeight));
    panBoundsRect.setOrigin(settings->cameraPanWidth / 2, settings->cameraPanHeight / 2);
    panBoundsRect.setPosition(window->getView().getCenter());
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

void Camera::centerOn(Entity *t)
{
    auto currentCenterView = window->getView();
    currentCenterView.setCenter(t->getPosition());
    std::cout << t->getPosition().x << ", " << t->getPosition().y << std::endl;
    window->setView(currentCenterView);
}

void Camera::drawBoundsRect()
{
    assert(window != 0);

    window->draw(panBoundsRect);
}