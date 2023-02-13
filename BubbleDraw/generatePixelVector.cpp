#include "generatePixelVector.h"

extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;

void generatePixelVector(std::vector<Circle>& circles, std::vector<SDL_Point>& pixels)
{
	pixels.clear();
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		for (int y = 0; y < SCREEN_HEIGHT; y++)
		{
			for (int i = 0; i < circles.size(); i++)
			{
				int a = x - circles[i].center.x;
				int b = y - circles[i].center.y;
				
				if (a * a + b * b <= circles[i].radius * circles[i].radius)
				{
					pixels.push_back({ x, y });
					break;
				}
			}
		}
	}
}
