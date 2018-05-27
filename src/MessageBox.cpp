#include "MessageBox.h"
#include "ResourceManager.h"

#include <iostream>

MessageBox::MessageBox()
{
    fontTexture = ResourceManager::getTexture("la-font.png");
}

MessageBox::~MessageBox()
{

}

void MessageBox::show()
{

}

void MessageBox::hide()
{

}

void MessageBox::setMessage(std::string message)
{
    const char* messageChars = message.c_str();
    int messageLength = message.length();

    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(messageLength * 4);

    for (int i=0; i < messageLength; i++)
    {
        char currentChar = messageChars[i];
        auto texCoords = textureCoordinatesForChar(currentChar);
        int u0 = texCoords.left;
        int v0 = texCoords.top;
        int u1 = texCoords.left + texCoords.width;
        int v1 = texCoords.top + texCoords.height;
        sf::Vertex* quad = &vertices[i * 4];

        quad[0].position = sf::Vector2f(i * 15, 0);
        quad[1].position = sf::Vector2f(i * 15 + 14, 0);
        quad[2].position = sf::Vector2f(i * 15 + 14, 14);
        quad[3].position = sf::Vector2f(i * 15, 14);

        quad[0].texCoords = sf::Vector2f(u0, v1);
        quad[1].texCoords = sf::Vector2f(u1, v1);
        quad[2].texCoords = sf::Vector2f(u1, v0);
        quad[3].texCoords = sf::Vector2f(u0, v0);

    }
}

sf::IntRect MessageBox::textureCoordinatesForChar(char c)
{
    switch (c)
    {
    case 'a': return sf::IntRect(0, 141, 14, 14);
    case 'b': return sf::IntRect(15, 141, 14, 14);
    case 'c': return sf::IntRect(29, 141, 14, 14);
    case 'd': return sf::IntRect(44, 141, 14, 14);
    case 'e': return sf::IntRect(59, 141, 14, 14);
    case 'f': return sf::IntRect(73, 141, 14, 14);
    case 'g': return sf::IntRect(88, 141, 14, 14);
    case 'h': return sf::IntRect(102, 141, 14, 14);
    case 'i': return sf::IntRect(117, 141, 14, 14);
    case 'j': return sf::IntRect(131, 141, 14, 14);
    case 'k': return sf::IntRect(146, 141, 14, 14);
    case 'l': return sf::IntRect(161, 141, 14, 14);
    case 'm': return sf::IntRect(175, 141, 14, 14);
    case 'n': return sf::IntRect(190, 141, 14, 14);
    case 'o': return sf::IntRect(0, 161, 14, 14);
    case 'p': return sf::IntRect(15, 161, 14, 14);
    case 'q': return sf::IntRect(29, 161, 14, 14);
    case 'r': return sf::IntRect(59, 161, 14, 14);
    case 's': return sf::IntRect(73, 161, 14, 14);
    case 't': return sf::IntRect(88, 161, 14, 14);
    case 'u': return sf::IntRect(102, 161, 14, 14);
    case 'v': return sf::IntRect(117, 161, 14, 14);
    case 'w': return sf::IntRect(131, 161, 14, 14);
    case 'x': return sf::IntRect(146, 161, 14, 14);
    case 'y': return sf::IntRect(161, 161, 14, 14);
    case 'z': return sf::IntRect(175, 161, 14, 14);
    case 'A': return sf::IntRect(0, 90, 14, 14);
    case 'B': return sf::IntRect(15, 90, 14, 14);
    case 'C': return sf::IntRect(29, 90, 14, 14);
    case 'D': return sf::IntRect(44, 90, 14, 14);
    case 'E': return sf::IntRect(59, 90, 14, 14);
    case 'F': return sf::IntRect(73, 90, 14, 14);
    case 'G': return sf::IntRect(88, 90, 14, 14);
    case 'H': return sf::IntRect(102, 90, 14, 14);
    case 'I': return sf::IntRect(117, 90, 14, 14);
    case 'J': return sf::IntRect(131, 90, 14, 14);
    case 'K': return sf::IntRect(146, 90, 14, 14);
    case 'L': return sf::IntRect(161, 90, 14, 14);
    case 'M': return sf::IntRect(175, 90, 14, 14);
    case 'N': return sf::IntRect(190, 90, 14, 14);
    case 'O': return sf::IntRect(0, 109, 14, 14);
    case 'P': return sf::IntRect(15, 109, 14, 14);
    case 'Q': return sf::IntRect(29, 109, 14, 14);
    case 'R': return sf::IntRect(44, 109, 14, 14);
    case 'S': return sf::IntRect(59, 109, 14, 14);
    case 'T': return sf::IntRect(73, 109, 14, 14);
    case 'U': return sf::IntRect(88, 109, 14, 14);
    case 'V': return sf::IntRect(102, 109, 14, 14);
    case 'W': return sf::IntRect(117, 109, 14, 14);
    case 'X': return sf::IntRect(131, 109, 14, 14);
    case 'Y': return sf::IntRect(146, 109, 14, 14);
    case 'Z': return sf::IntRect(161, 109, 14, 14);
    case '.': return sf::IntRect(226, 57, 14, 14);
    case ' ': return sf::IntRect(175, 109, 14, 14);
    default:
        std::cout << "unexpected character " << c << std::endl;
        return sf::IntRect(175, 109, 14, 14);
    }
}

void MessageBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    states.transform *= getTransform();
    states.texture = fontTexture;
    target.draw(vertices, states);
}