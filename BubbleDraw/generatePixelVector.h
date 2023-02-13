#pragma once
#include <SDL.h>
#include <vector>
#include "Structs/primitiveStructs.h"

void generatePixelVector(std::vector<Circle>& circles, std::vector<SDL_Point>& pixels);