#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include "primitiveStructs.h"
#undef main

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius);

int main()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event e;
	SDL_Init(SDL_INIT_EVERYTHING);
	bool running = true;
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);




	//Initialize mouse position and radius setting.
	int xMouse = 0;
	int yMouse = 0;
	int radius = 100;

	//Initialize circle vector. The 0 index circle is reserved for the mouse circle.
	std::vector<Circle> circles;
	circles.push_back({ SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100 });

	while (running)
	{
		//Set draw color to black and clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		//Set draw color to white
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		
		//TODO: Refactor into a new file.
		while (SDL_PollEvent(&e))
		{
			if (e.type == SDL_QUIT)
			{
				running = false;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_ESCAPE:
					running = false;
					break;
				}
			}
			else if (e.type == SDL_KEYUP)
			{
				
			}
			else if (e.type == SDL_MOUSEMOTION)
			{
				SDL_GetMouseState(&xMouse, &yMouse);
			}
			else if (e.type == SDL_MOUSEWHEEL)
			{
				if (e.wheel.y > 0)
				{
					radius += 10;
					std::cout << "Radius: " << radius << std::endl;
				}
				else if (e.wheel.y < 0)
				{
					if (radius > 10)
						radius -= 10;
					std::cout << "Radius: " << radius << std::endl;
				}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					circles.push_back({ xMouse, yMouse, radius });
				}
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{

			}
		}
		
		circles[0] = { xMouse, yMouse, radius };

		for (size_t i = 0; i < circles.size(); i++)
		{
			DrawCircle(renderer, circles[i].x, circles[i].y, circles[i].radius);
		}
		
		SDL_RenderPresent(renderer);
	}
}

//TODO: Refactor into a new file.
void DrawCircle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius)
{
	const int32_t diameter = (radius * 2);

	int32_t x = (radius - 1);
	int32_t y = 0;
	int32_t tx = 1;
	int32_t ty = 1;
	int32_t error = (tx - diameter);

	while (x >= y)
	{
		//  Each of the following renders an octant of the circle
		SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
		SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
		SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

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
}