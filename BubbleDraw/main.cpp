#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "SDL_Util.h"
#include "primitiveStructs.h"
#include "drawCircle.h"
#include "bowyerWatsonAlgorithm.h"
#undef main

//Screen dimension constants
extern const int SCREEN_WIDTH = 1000;
extern const int SCREEN_HEIGHT = 600;



//Initialize mouse position and radius setting.
SDL_Point mousePos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
int radiusSetting = 100;

SDL_Event e;
bool running = true;


Circle* findCircleWithCenter(SDL_Point& center, std::vector<Circle>& circles);

int main()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	


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
		
		//TODO: Refactor into a new file
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
				case SDLK_c:
					circles.clear();
					circles.push_back({ {0, 0}, 0 });
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
					radiusSetting += 10;
					std::cout << "Radius: " << radiusSetting << std::endl;
				}
				else if (e.wheel.y < 0)
				{
					if (radiusSetting > 10)
						radiusSetting -= 10;
					std::cout << "Radius: " << radiusSetting << std::endl;
				}
			}
			else if (e.type == SDL_MOUSEBUTTONDOWN)
			{
				if (e.button.button == SDL_BUTTON_LEFT)
				{
					circles.push_back({ mousePos.x, mousePos.y, radiusSetting });
				}
			}
			else if (e.type == SDL_MOUSEBUTTONUP)
			{

			}
		}
		
		//Update mouse circle
		circles[0] = { mousePos.x, mousePos.y, radiusSetting };

		//Generate list of circle centers
		std::vector<SDL_Point> circleCenters;
		for (size_t i = 0; i < circles.size(); i++)
		{
			circleCenters.push_back(circles[i].center);
		}
		//Generate Delaunay Triangulation
		std::vector<Triangle> delaunayTriangles = BowyerWatsonAlgorithm(circleCenters);
		
		//Find circle adjacencies using triangulation
		for (size_t i = 0; i < delaunayTriangles.size(); i++)
		{
			Circle* circle1 = findCircleWithCenter(delaunayTriangles[i].p1, circles);
			Circle* circle2 = findCircleWithCenter(delaunayTriangles[i].p2, circles);
			Circle* circle3 = findCircleWithCenter(delaunayTriangles[i].p3, circles);

			if (circle1 != nullptr && circle2 != nullptr)
			{
				circle1->adjacentCircles.insert(circle2);
				circle2->adjacentCircles.insert(circle1);
			}
			if (circle2 != nullptr && circle3 != nullptr)
			{
				circle2->adjacentCircles.insert(circle3);
				circle3->adjacentCircles.insert(circle2);
			}
			if (circle3 != nullptr && circle1 != nullptr)
			{
				circle3->adjacentCircles.insert(circle1);
				circle1->adjacentCircles.insert(circle3);
			}
		}
		for (size_t i = 0; i < circles.size(); i++)
		{
			std::vector<SDL_Point> circleData = PixelizeCircle(circles[i].center, circles[i].radius);
			SDL_RenderDrawPoints(renderer, circleData.data(), circleData.size());
		}
		//Clear adjacent circles
		for (size_t i = 0; i < circles.size(); i++)
		{
			circles[i].adjacentCircles.clear();
		}
		
		
		//Draw Delaunay Triangulation
		for (size_t i = 0; i < delaunayTriangles.size(); i++)
		{
			SDL_RenderDrawLine(renderer, delaunayTriangles[i].p1.x, delaunayTriangles[i].p1.y, delaunayTriangles[i].p2.x, delaunayTriangles[i].p2.y);
			SDL_RenderDrawLine(renderer, delaunayTriangles[i].p2.x, delaunayTriangles[i].p2.y, delaunayTriangles[i].p3.x, delaunayTriangles[i].p3.y);
			SDL_RenderDrawLine(renderer, delaunayTriangles[i].p3.x, delaunayTriangles[i].p3.y, delaunayTriangles[i].p1.x, delaunayTriangles[i].p1.y);
		}

		
		SDL_RenderPresent(renderer);
	}
}


Circle* findCircleWithCenter(SDL_Point &center, std::vector<Circle> &circles)
{
	Circle* output = nullptr;
	for (Circle circle : circles)
	{
		if (circle.center == center)
			return output = &circle;
	}
	return output;
}