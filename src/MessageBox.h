#ifndef MESSAGEBOX_H_INCLUDED
#define MESSAGEBOX_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

class MessageBox : public sf::Drawable, public sf::Transformable
{
public:
    MessageBox();
    ~MessageBox();

    void setMessage(std::string message);
    void update();

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    sf::IntRect textureCoordinatesForChar(char c);

    std::string message;
    sf::RectangleShape messageBackground;
    sf::Texture *fontTexture;
    sf::VertexArray vertices;

};

#endif