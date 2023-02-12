#pragma once
#include <vector>
#include <SDL.h>
#include "../Structs/primitiveStructs.h"


std::vector<SDL_Point> PixelizeCircle(int indexOfCircle, std::vector<Circle> circles);