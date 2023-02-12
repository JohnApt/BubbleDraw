#include "SDL_Util.h"
#include <cmath>
#include <SDL.h>

double distanceBetweenPoints(SDL_Point point1, SDL_Point point2)
{
return sqrt(pow(point1.x - point2.x, 2) + pow(point1.y - point2.y, 2));
}