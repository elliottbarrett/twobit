#include "Camera.h"

void Camera::init(sf::RenderWindow *window)
{
    this->window = window;
}

void Camera::update(float dt)
{

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

void Camera::centerOn(sf::Transformable &t)
{
    auto currentCenterView = window->getView();
    currentCenterView.setCenter(t.getPosition());
    window->setView(currentCenterView);
}