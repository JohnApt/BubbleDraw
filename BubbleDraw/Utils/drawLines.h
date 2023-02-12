#pragma once
#include <vector>
#include <SDL.h>
#include "../Structs/primitiveStructs.h"

std::vector<SDL_Point> PixelizeLines(std::vector<Triangle> triangles, std::vector<Circle> circles);