#ifndef SFMATH_INCLUDED
#define SFMATH_INCLUDED

#include <math.h>

inline float length(sf::Vector2f v)
{
    return sqrt(v.x * v.x + v.y * v.y);
}

inline float distance(sf::Vector2f a, sf::Vector2f b) 
{
    return sqrt((b.x - a.x) * (b.x - a.x) + (b.y - a.y) * (b.y - a.y));
}

inline sf::Vector2f normalize(sf::Vector2f v)
{
    return sf::Vector2f(v.x / length(v), v.y / length(v));
}

inline float clamp(float v, float lo, float hi)
{
    return v < lo ? lo : (v > hi ? hi : v);
}

#endif