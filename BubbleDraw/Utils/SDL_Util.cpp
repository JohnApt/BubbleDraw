#include <cmath>
#include <SDL.h>
#include "SDL_Util.h"

double distanceBetweenPoints(SDL_Point point1, SDL_Point point2)
{
	int a = point1.x - point2.x;
	int b = point1.y - point2.y;
	return sqrt(a * a + b * b);
}