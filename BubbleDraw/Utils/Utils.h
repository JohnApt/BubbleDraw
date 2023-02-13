#pragma once
#include "Structs/primitiveStructs.h"

int findCircleIndexWithCenter(SDL_Point& center, std::vector<Circle>& circles);

void generateCircleAdjacencies(std::vector<Circle>& circles);

bool isAdjacentTo(Circle circle1, Circle circle2);

void clearCircleAdjacencies(std::vector<Circle>& circles);

bool isWithinVoronoiCell(SDL_Point point, int indexOfCircle, std::vector<Circle>& circles);