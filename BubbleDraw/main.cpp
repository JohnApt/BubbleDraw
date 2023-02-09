#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include "primitiveStructs.h"
#include "drawCircle.h"
#undef main

//Screen dimension constants
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 600;

int main()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	SDL_Event e;
	SDL_Init(SDL_INIT_EVERYTHING);
	bool running = true;
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	//Initialize mouse position and radius setting.
	SDL_Point mousePos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
	int radius = 100;

	//Initialize circle vector. The 0 index circle is reserved for the mouse circle.
	std::vector<Circle> circles;
	circles.push_back({ {0, 0}, 0 });

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
				SDL_GetMouseState(&mousePos.x, &mousePos.y);
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
					circles.push_back({ mousePos.x, mousePos.y, radius });
				}
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{

			}
		}
		
		//Draw mouse circle
		circles[0] = { mousePos.x, mousePos.y, radius };

		for (size_t i = 0; i < circles.size(); i++)
		{
			std::vector<SDL_Point> circleData = PixelizeCircle(circles[i].center, circles[i].radius);
			SDL_RenderDrawPoints(renderer, circleData.data(), circleData.size());
		}
		
		SDL_RenderPresent(renderer);
	}
}