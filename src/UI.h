#ifndef UI_H_INCLUDED
#define UI_H_INCLUDED

#include <SFML/Graphics.hpp>

#include "MessageBox.h"
#include "Player.h"

class Player;

class UI
{
public:
    static void init(sf::RenderWindow &window);
    static void handleResize(unsigned int newWidth, unsigned int newHeight);
    static void update(float dt);
    static void draw(sf::RenderWindow &window);
    static void showMessage(std::string message);
    static void hideMessage();

private:
    static sf::IntRect getPlayerItemTextureRect(PlayerItem item);

    static sf::Sprite playerOneItemBG;
    static sf::Sprite playerOneItem;
    static sf::Sprite playerOneIndicator;
    
    static sf::Sprite playerTwoItemBG;
    static sf::Sprite playerTwoItem;
    static sf::Sprite playerTwoIndicator;

    static MessageBox messageBox;
    static bool messageVisible;

    static Player* playerOne;
    static Player* playerTwo;
};

#endif