#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "EventHandler.h"
#include "Utils/SDL_Util.h"
#include "Structs/primitiveStructs.h"
#include "Utils/drawCircle.h"
#include "Utils/drawLines.h"
#include "AbstractAlgorithms/bowyerWatsonAlgorithm.h"
#include "Utils/Utils.h"
#undef main

//Configuration:

SDL_Event e;
bool running = true;

//Screen dimension constants
extern const int SCREEN_WIDTH = 1920;
extern const int SCREEN_HEIGHT = 1080;

//Initialize mouse position and radius setting.
SDL_Point mousePos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
int radiusSetting = 100;

//Turn on Dalaunay triangulation
bool triangulation = true;

//End of Configuration


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

		//call event handler
		EventHandler(e, running, circles, mousePos, radiusSetting);
		
		//Update mouse circle
		circles[0] = { mousePos.x, mousePos.y, radiusSetting };

		//Generate list of circle centers
		std::vector<SDL_Point> circleCenters;
		for (size_t i = 0; i < circles.size(); i++)
		{
			circleCenters.push_back(circles[i].center);
		}
		
		//Clear circle adjacencies
		for (size_t i = 0; i < circles.size(); i++)
		{
			circles[i].adjacentCircleIndices.clear();
		}
		
		//Generate circle adjacencies
		generateCircleAdjacencies(circles);
		
		for (size_t i = 0; i < circles.size(); i++)
		{
			std::vector<SDL_Point> circleData = PixelizeCircle(i, circles);
			SDL_RenderDrawPoints(renderer, circleData.data(), circleData.size());
		}
		
		if (triangulation && circles.size() > 2)
		{
			//Generate Delaunay Triangulation
			std::vector<Triangle> delaunayTriangles = BowyerWatsonAlgorithm(circleCenters);

			//Draw Delaunay Triangulation
			for (size_t i = 0; i < delaunayTriangles.size(); i++)
			{
				SDL_RenderDrawLine(renderer, delaunayTriangles[i].p1.x, delaunayTriangles[i].p1.y, delaunayTriangles[i].p2.x, delaunayTriangles[i].p2.y);
				SDL_RenderDrawLine(renderer, delaunayTriangles[i].p2.x, delaunayTriangles[i].p2.y, delaunayTriangles[i].p3.x, delaunayTriangles[i].p3.y);
				SDL_RenderDrawLine(renderer, delaunayTriangles[i].p3.x, delaunayTriangles[i].p3.y, delaunayTriangles[i].p1.x, delaunayTriangles[i].p1.y);
			}
		}
		
		SDL_RenderPresent(renderer);
	}
}