#ifndef GAMECONTEXT_H_INCLUDED
#define GAMECONTEXT_H_INCLUDED

namespace sf
{
    class RenderWindow;
}

class GameContext
{
public:
    GameContext();
    virtual void update(float dt);
    virtual void render(sf::RenderWindow &window);

protected:

};

#endif