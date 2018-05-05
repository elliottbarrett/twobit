#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <map>

#define GB_WIDTH 160
#define GB_HEIGHT 144
#define WINDOW_SCALE 4

// typedef std::map<std::string, 

class Game
{

};

class Context
{

};

struct AnimationFrame
{
    int x;
    int y;
    int width;
    int height;

    AnimationFrame(int _x, int _y, int _width, int _height) :
        x(_x), y(_y), width(_width), height(_height) 
    {

    }
};

class Animation
{
    std::string name;
    std::vector<AnimationFrame> frames;
    float timePerFrame;
    float timeInFrame;
    int currentFrame;

public:
    Animation(std::string _name, std::vector<AnimationFrame> _frames, float _timePerFrame) :
        name(_name), frames(_frames), timePerFrame(_timePerFrame), timeInFrame(0), currentFrame(0)
    {

    }

    void update(float dt)
    {
        timeInFrame += dt;

        if (timeInFrame >= timePerFrame) 
        {
            currentFrame = (currentFrame + 1 == frames.size() ? 0 : currentFrame + 1);
        }
    }
};

class Sprite : public sf::Drawable, public sf::Transformable
{
// Members
    Animation currentAnimation;

    sf::Texture* texture;
    sf::Vertex vertices[4];

// Methods
public:
    Sprite(Animation _currentAnimation, sf::Texture* _texture) :
        currentAnimation(_currentAnimation), texture(_texture)
    {

    }

    void update(float dt)
    {
        currentAnimation.update(dt);
    }

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        // target.draw( , states);
    }
};

Sprite makeTestSprite(sf::Texture* texture) 
{
    auto frame0 = AnimationFrame(0,0,16,16);
    auto frame1 = AnimationFrame(0,16,16,16);
    auto frame2 = AnimationFrame(0,32,16,16);
    auto frame3 = AnimationFrame(0,48,16,16);

    float frameTime = 0.3f;
    std::vector<AnimationFrame> frames = { frame0, frame1, frame2, frame3 };

    auto testAnimation = Animation("testAnimation", frames, frameTime);

    return Sprite(testAnimation, texture);
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(GB_WIDTH * WINDOW_SCALE, GB_HEIGHT * WINDOW_SCALE), "SFML works!");
    sf::Clock frameTimeClock;
    window.setVerticalSyncEnabled(true);

    sf::Texture pokemonTexture;
    pokemonTexture.loadFromFile("pokemon.png");
    auto pokemonSprite = sf::Sprite(pokemonTexture);
    pokemonSprite.setScale(WINDOW_SCALE, WINDOW_SCALE);

    auto testSprite = makeTestSprite(&pokemonTexture);

    while (window.isOpen())
    {
        sf::Event event;
        sf::Time frameTime = frameTimeClock.restart();
        float dt = frameTime.asSeconds();

        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyReleased)
                window.close();
        }

        testSprite.update(dt);

        window.clear();
        // window.draw(pokemonSprite);
        window.draw(testSprite);
        window.display();
    }

    return 0;
}