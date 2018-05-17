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

    if (followEntity)
    {
        auto ePos = followEntity->getPosition();
        float hw = 0.5 * settings->cameraPanWidth;
        float hh = 0.5 * settings->cameraPanHeight;

        // TODO: There's probably better math for this. I don't care about that right now.
        if (!panBoundsRect.getGlobalBounds().contains(ePos))
        {
            auto cPos = panBoundsRect.getPosition();
            float dx = 0;
            float dy = 0;

            bool moveInX = ePos.x > cPos.x + hw || ePos.x < cPos.x - hw;
            bool moveInY = ePos.y > cPos.y + hh || ePos.y < cPos.y - hh;

            if (moveInX)
            {
                if (ePos.x > cPos.x)
                {
                    dx = ePos.x - cPos.x - hw;
                }
                else
                {
                    dx = ePos.x - cPos.x + hw;
                }
            }

            if (moveInY)
            {
                if (ePos.y > cPos.y)
                {
                    dy = ePos.y - cPos.y - hw;
                }
                else
                {
                    dy = ePos.y - cPos.y + hw;
                }
            }

            cPos = panBoundsRect.getPosition();
            auto currentCenterView = window->getView();
            currentCenterView.move(sf::Vector2f(dx, dy));
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
    std::cout << t->getPosition().x << ", " << t->getPosition().y << std::endl;
    window->setView(currentCenterView);
}

void Camera::drawBoundsRect()
{
    assert(window != 0);

    window->draw(panBoundsRect);
}