#include "Player.h"
#include "ArcadeInput.h"
#include "Settings.h"
#include "ResourceManager.h"

Player::Player(unsigned int id, std::string name, std::vector<std::string> params) :
    Entity(id, name, params),
    playerNumber(name == "Player1" ? 1 : 2),
    isOnGround(true), wasOnGround(true),
    isAtCeiling(false), wasAtCeiling(false),
    isPushingLeftWall(false), wasPushingLeftWall(false),
    isPushingRightWall(false), wasPushingRightWall(false)
{
    collisionRect = sf::RectangleShape(sf::Vector2f(16,16));
    collisionRect.setFillColor(sf::Color::Transparent);
    collisionRect.setOutlineColor(sf::Color(255,0,255));
    collisionRect.setOutlineThickness(-1);
    move(20,20);

    setOrigin(8,0);

    initParameters(params);
}

Player::~Player()
{
}

void Player::initParameters(std::vector<std::string> params)
{
    sf::Vector2f pos;
    for (auto it : params)
    {
        auto key = it.substr(0, it.find(" "));
        auto value = it.substr(it.find(" ") + 1);
        
        if (key == "posX") pos.x = std::stof(value);
        else if (key == "posY") pos.y = std::stof(value);
        else if (key == "playerNum") playerNumber = std::stoi(value);
        else if (key == "texture") setTexture(ResourceManager::getTexture(value));
    }
    setPosition(pos);
}

std::string Player::getEntityDescription()
{
    return std::to_string(id) + " Player " + name + "\n"
        + writeParameter("playerNum", playerNumber)
        + writeParameter("posX", getPosition().x)
        + writeParameter("posY", getPosition().y);

}

void Player::update(float dt)
{
    AnimatedSprite::update(dt);

    InputState input = playerNumber == 1 ? ArcadeInput::getPlayerOneState() : ArcadeInput::getPlayerTwoState();
    auto settings = &Settings::instance();

    if (input.direction & JoyDirection::LEFT)
    {
        velocity.x = -1 * settings->walkSpeed;
    }
    else if (input.direction & JoyDirection::RIGHT)
    {
        velocity.x = settings->walkSpeed;
    }
    else
    {
        velocity.x = 0;
    }

    if (input.direction & JoyDirection::UP)
    {
        if (isOnGround)
        {
            isOnGround = false;
            velocity.y = settings->jumpSpeed;
        }
    }
    if (input.direction & JoyDirection::DOWN)
    {
        // move(0,-1);
    }

    if (!isOnGround)
    {
        velocity.y += settings->gravity * dt;
    }

    if (input.rightButton) // this is z
    {
        velocity.y = settings->jumpSpeed;
    }

    updatePhysics();
    move(velocity * dt);
}

void Player::updatePhysics()
{
    wasOnGround = isOnGround;
    wasAtCeiling = isAtCeiling;
    wasPushingLeftWall = isPushingLeftWall;
    wasPushingRightWall = isPushingRightWall;    
}

sf::FloatRect Player::getCollisionBounds()
{
    auto transform = getTransform();
    sf::FloatRect bounds = transform.transformRect(sf::FloatRect(1,0,14,16));
    return bounds;
}

void Player::handleWorldCollision(bool didCollide)
{
    if (didCollide)
    {
        velocity.y = 0;
    }

    isOnGround = didCollide;
}

void Player::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    auto settings = &Settings::instance();

    AnimatedSprite::draw(target, states);
    states.transform *= getTransform();

    if (settings->drawEntityCollisionBounds)
    {
        target.draw(collisionRect, states);
    }   
}

void Player::drawInspectorWidgets()
{
    Entity::drawInspectorWidgets();
}