#pragma once
#include "../Structs/primitiveStructs.h"

int findCircleIndexWithCenter(SDL_Point& center, std::vector<Circle>& circles);

void generateCircleAdjacencies(std::vector<Circle>& circles, std::vector<Triangle>& delaunayTriangles);

void clearCircleAdjacencies(std::vector<Circle>& circles);

bool isWithinVoronoiCell(SDL_Point point, int indexOfCircle, std::vector<Circle>& circles);