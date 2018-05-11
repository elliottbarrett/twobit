#ifndef MESSAGEBOX_H_INCLUDED
#define MESSAGEBOX_H_INCLUDED

#include <SFML/Graphics.hpp>
#include <string>

class MessageBox : public sf::Drawable, sf::Transformable
{
public:
    MessageBox();
    ~MessageBox();

private:
    std::string message;
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif