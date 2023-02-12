#include "drawCircle.h"
#include "../Utils/Utils.h"
#include <math.h>
#include <vector>
#include <stdio.h>

std::vector<SDL_Point> PixelizeCircle(int indexOfCircle, std::vector<Circle> circles)
{
	std::vector<SDL_Point> pixels;
	int radius = circles[indexOfCircle].radius;
	int x = 0;
	int y = radius;
	int d = 3 - 2 * radius;
	while (y >= x)
	{
		if (isWithinVoronoiCell({ circles[indexOfCircle].center.x + x, circles[indexOfCircle].center.y + y }, indexOfCircle, circles))
			pixels.push_back({ circles[indexOfCircle].center.x + x, circles[indexOfCircle].center.y + y });
		if (isWithinVoronoiCell({ circles[indexOfCircle].center.x + y, circles[indexOfCircle].center.y + x }, indexOfCircle, circles))
			pixels.push_back({ circles[indexOfCircle].center.x + y, circles[indexOfCircle].center.y + x });
		if (isWithinVoronoiCell({ circles[indexOfCircle].center.x - x, circles[indexOfCircle].center.y + y }, indexOfCircle, circles))
			pixels.push_back({ circles[indexOfCircle].center.x - x, circles[indexOfCircle].center.y + y });
		if (isWithinVoronoiCell({ circles[indexOfCircle].center.x - y, circles[indexOfCircle].center.y + x }, indexOfCircle, circles))
			pixels.push_back({ circles[indexOfCircle].center.x - y, circles[indexOfCircle].center.y + x });
		if (isWithinVoronoiCell({ circles[indexOfCircle].center.x + x, circles[indexOfCircle].center.y - y }, indexOfCircle, circles))
			pixels.push_back({ circles[indexOfCircle].center.x + x, circles[indexOfCircle].center.y - y });
		if (isWithinVoronoiCell({ circles[indexOfCircle].center.x + y, circles[indexOfCircle].center.y - x }, indexOfCircle, circles))
			pixels.push_back({ circles[indexOfCircle].center.x + y, circles[indexOfCircle].center.y - x });
		if (isWithinVoronoiCell({ circles[indexOfCircle].center.x - x, circles[indexOfCircle].center.y - y }, indexOfCircle, circles))
			pixels.push_back({ circles[indexOfCircle].center.x - x, circles[indexOfCircle].center.y - y });
		if (isWithinVoronoiCell({ circles[indexOfCircle].center.x - y, circles[indexOfCircle].center.y - x }, indexOfCircle, circles))
			pixels.push_back({ circles[indexOfCircle].center.x - y, circles[indexOfCircle].center.y - x });
		
		
		x++;
		if (d > 0)
		{
			y--;
			d = d + 4 * (x - y) + 10;
		}
		else
		{
			d = d + 4 * x + 6;
		}
	}
	return pixels;
}