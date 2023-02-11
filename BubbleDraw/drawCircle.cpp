#include <math.h>
#include <vector>
#include <SDL.h>
#include <stdio.h>
#include "primitiveStructs.h"


//TODO: Refactor into a new file.
// rounding helper, simplified version of the function I use
int roundUpToMultipleOfEight(int v)
{
	return (v + (8 - 1)) & -8;
}

std::vector<SDL_Point> PixelizeCircle(int indexOfCircle, std::vector<Circle> circles)
{
	std::vector<SDL_Point> pixels;
	
	return pixels;
}