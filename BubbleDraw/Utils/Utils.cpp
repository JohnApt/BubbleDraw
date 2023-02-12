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
void generateCircleAdjacencies(std::vector<Circle>& circles)
{
	for (size_t i = 0; i < circles.size(); i++)
	{
		for (size_t j = 0; j < circles.size(); j++)
		{
			if (i != j)
			{
				if (isAdjacentTo(circles[i], circles[j]))
				{
					circles[i].adjacentCircleIndices.push_back(j);
				}
			}
		}
	}
	
}

bool isAdjacentTo(Circle circle1, Circle circle2)
{
	return (circle1.center.x - circle2.center.x) * (circle1.center.x - circle2.center.x) + (circle1.center.y - circle2.center.y) * (circle1.center.y - circle2.center.y) <= (circle1.radius + circle2.radius) * (circle1.radius + circle2.radius);
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
