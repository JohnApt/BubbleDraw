#pragma once
#include <vector>
#include <SDL.h>
#include "../Structs/primitiveStructs.h"

void drawLines(std::vector<Triangle> triangles, std::vector<Circle> circles, SDL_Renderer* gRenderer);