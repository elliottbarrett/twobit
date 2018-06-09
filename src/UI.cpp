#include "UI.h"
#include "ResourceManager.h"
#include "Player.h"
#include "Entities.h"

Player* UI::playerOne = nullptr;
Player* UI::playerTwo = nullptr;
sf::Sprite UI::playerOneItemBG = sf::Sprite();
sf::Sprite UI::playerTwoItemBG = sf::Sprite();
sf::Sprite UI::playerOneItem = sf::Sprite();
sf::Sprite UI::playerTwoItem = sf::Sprite();
sf::Sprite UI::playerOneIndicator = sf::Sprite();
sf::Sprite UI::playerTwoIndicator = sf::Sprite();

MessageBox UI::messageBox = MessageBox();
bool UI::messageVisible = false;

void UI::init(sf::RenderWindow &window)
{
    auto windowSize = window.getSize();

    messageBox.setPosition(100,510);
    messageBox.setScale(2,2);

    playerOneItem.setTexture(*ResourceManager::getTexture("ui.png"));
    playerTwoItem.setTexture(*ResourceManager::getTexture("ui.png"));
    playerOneItemBG.setTexture(*ResourceManager::getTexture("ui.png"));
    playerTwoItemBG.setTexture(*ResourceManager::getTexture("ui.png"));
    playerOneIndicator.setTexture(*ResourceManager::getTexture("ui.png"));
    playerTwoIndicator.setTexture(*ResourceManager::getTexture("ui.png"));

    playerOne = (Player*)Entities::getByName("Player1");
    playerTwo = (Player*)Entities::getByName("Player2");

    handleResize(windowSize.x, windowSize.y);
}

void UI::handleResize(unsigned int newWidth, unsigned int newHeight)
{
    auto pixelsPerBlock = newHeight / 9;
    
    updateItemRects();

    playerOneItemBG.setScale(pixelsPerBlock / 16, pixelsPerBlock / 16);
    playerOneItem.setScale(pixelsPerBlock / 16, pixelsPerBlock / 16);
    playerOneIndicator.setScale(pixelsPerBlock / 16, pixelsPerBlock / 16);

    playerTwoItemBG.setScale(pixelsPerBlock / 16, pixelsPerBlock / 16);
    playerTwoItem.setScale(pixelsPerBlock / 16, pixelsPerBlock / 16);
    playerTwoIndicator.setScale(pixelsPerBlock / 16, pixelsPerBlock / 16);

    playerOneItem.setPosition(8, 8);
    playerOneItemBG.setPosition(8, 8);
    playerOneIndicator.setPosition(8, 8);

    playerTwoItem.setPosition(8, (playerOneItem.getScale().y * 16) + 16);
    playerTwoItemBG.setPosition(8, (playerOneItem.getScale().y * 16) + 16);
    playerTwoIndicator.setPosition(8, (playerOneItem.getScale().y * 16) + 16);
}

sf::IntRect UI::getPlayerItemTextureRect(PlayerItem item)
{
    switch (item)
    {
    case PI_NONE:
        return sf::IntRect(0,0,0,0);
    case PI_STICK:
        return sf::IntRect(0,16,16,16);
    case PI_BALL:
        return sf::IntRect(16,16,16,16);
    default:
        return sf::IntRect(0,0,0,0);
    }
}

void UI::draw(sf::RenderWindow &window)
{
    // TODO - window.getDefaultView should be replaced with something inside the camera class
    auto gameView = window.getView();
    auto uiView = window.getDefaultView();

    window.setView(uiView);

    window.draw(playerOneItemBG);
    window.draw(playerOneItem);
    window.draw(playerOneIndicator);
    window.draw(playerTwoItemBG);
    window.draw(playerTwoItem);
    window.draw(playerTwoIndicator);

    if (messageVisible)
    {
        auto messageView = window.getDefaultView();
        messageView.setSize(messageView.getSize().x, -messageView.getSize().y);
        window.setView(messageView);
        window.draw(messageBox);
    }

    window.setView(gameView);
}


void UI::update(float dt)
{
    // update 
}

void UI::updateItemRects()
{
    auto playerOneItemRect = getPlayerItemTextureRect(playerOne->getCurrentItem());
    auto playerTwoItemRect = getPlayerItemTextureRect(playerTwo->getCurrentItem());

    playerOneItemBG.setTextureRect(sf::IntRect(0, 0, 16, 16));
    playerOneItem.setTextureRect(playerOneItemRect);
    playerOneIndicator.setTextureRect(sf::IntRect(16, 0, 16, 16));

    playerTwoItemBG.setTextureRect(sf::IntRect(0, 0, 16, 16));
    playerTwoItem.setTextureRect(playerTwoItemRect);
    playerTwoIndicator.setTextureRect(sf::IntRect(32, 0, 16, 16));    
}

void UI::showMessage(std::string message)
{
    messageVisible = true;
    messageBox.setMessage(message);
}

void UI::hideMessage()
{
    messageVisible = false;
}
