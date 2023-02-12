#include <math.h>
#include <vector>
#include <SDL.h>
#include <stdio.h>
#include "Utils.h"

int findCircleIndexWithCenter(SDL_Point& center, std::vector<Circle>& circles)
{
	for (size_t i = 0; i < circles.size(); i++)
	{
		if (circles[i].center.x == center.x && circles[i].center.y == center.y)
		{
			return i;
		}
	}
	return -1;
}

//Generate a list of adjacent circles for each circle
void generateCircleAdjacencies(std::vector<Circle>& circles, std::vector<Triangle>& delaunayTriangles)
{
	for (size_t i = 0; i < delaunayTriangles.size(); i++)
	{
		int circle1Index = findCircleIndexWithCenter(delaunayTriangles[i].p1, circles);
		int circle2Index = findCircleIndexWithCenter(delaunayTriangles[i].p2, circles);
		int circle3Index = findCircleIndexWithCenter(delaunayTriangles[i].p3, circles);

		if (circle1Index != -1 && circle2Index != -1)
		{
			circles[circle1Index].adjacentCircleIndices.insert(circle2Index);
			circles[circle2Index].adjacentCircleIndices.insert(circle1Index);
		}
		if (circle2Index != -1 && circle3Index != -1)
		{
			circles[circle2Index].adjacentCircleIndices.insert(circle3Index);
			circles[circle3Index].adjacentCircleIndices.insert(circle2Index);
		}
		if (circle1Index != -1 && circle3Index != -1)
		{
			circles[circle1Index].adjacentCircleIndices.insert(circle3Index);
			circles[circle3Index].adjacentCircleIndices.insert(circle1Index);
		}
	}
}

//Clear adjacent circle indices
void clearCircleAdjacencies(std::vector<Circle>& circles)
{
	for (size_t i = 0; i < circles.size(); i++)
	{
		circles[i].adjacentCircleIndices.clear();
	}
}

bool isWithinVoronoiCell(SDL_Point point, int indexOfCircle, std::vector<Circle>& circles)
{
	Circle& circle = circles[indexOfCircle];

	for (auto it = circle.adjacentCircleIndices.begin(); it != circle.adjacentCircleIndices.end(); it++)
	{
		if (circle.powerOfPoint(point) > circles[*it].powerOfPoint(point))
		{
			return false;
		}
	}
	return true;
}
