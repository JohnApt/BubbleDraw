#pragma once
#include <SDL.h>

inline bool operator==(SDL_Point const& a, SDL_Point const& b)
{
    return a.x == b.x && a.y == b.y;
}

inline bool operator!=(SDL_Point const& a, SDL_Point const& b)
{
    return !(a == b);
}

double distanceBetweenPoints(SDL_Point point1, SDL_Point point2);