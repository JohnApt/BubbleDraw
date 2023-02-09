#include <math.h>
#include <vector>
#include <SDL.h>
#include <stdio.h>


//TODO: Refactor into a new file.
// rounding helper, simplified version of the function I use
int roundUpToMultipleOfEight(int v)
{
	return (v + (8 - 1)) & -8;
}

std::vector<SDL_Point> PixelizeCircle(SDL_Point center, int radius)
{
	std::vector<SDL_Point> points;

	// 35 / 49 is a slightly biased approximation of 1/sqrt(2)
	const int arrSize = roundUpToMultipleOfEight(radius * 8 * 35 / 49);
	points.reserve(arrSize);

	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		// Each of the following renders an octant of the circle
		points.push_back({ center.x + x, center.y - y });
		points.push_back({ center.x + x, center.y + y });
		points.push_back({ center.x - x, center.y - y });
		points.push_back({ center.x - x, center.y + y });
		points.push_back({ center.x + y, center.y - x });
		points.push_back({ center.x + y, center.y + x });
		points.push_back({ center.x - y, center.y - x });
		points.push_back({ center.x - y, center.y + x });

		if (error <= 0)
		{
			++y;
			error += ty;
			ty += 2;
		}

		if (error > 0)
		{
			--x;
			tx += 2;
			error += (tx - diameter);
		}
	}

	return points; // RVO FTW
}