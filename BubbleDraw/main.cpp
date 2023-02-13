#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include "EventHandler.h"
#include "Utils/SDL_Util.h"
#include "Utils/Utils.h"
#include "Structs/primitiveStructs.h"
#include "generatePixelVector.h"
#include "AbstractAlgorithms/bowyerWatsonAlgorithm.h"

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
bool triangulation = false;

//End of Configurations

int main()
{
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	
	SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, 0, &window, &renderer);

	//Initialize circle vector. The 0 index circle is reserved for the mouse circle.
	std::vector<Circle> circles;
	circles.push_back({ {0, 0}, 0 });

	std::vector<SDL_Point> pixels;

	while (running)
	{
		//Set draw color to black and clear screen
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		
		//Set draw color to white
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

		//Call event handler
		EventHandler(e, running, circles, mousePos, radiusSetting, triangulation);
		
		//Clear and then regenerate circle adjacencies
		clearCircleAdjacencies(circles);
		generateCircleAdjacencies(circles);

		//Generate and draw pixel vector
		generatePixelVector(circles, pixels);
		SDL_RenderDrawPoints(renderer, &pixels[0], pixels.size());
		

		if (triangulation && circles.size() > 2)
		{
			//Generate list of circle centers for Delaunay triangulation
			std::vector<SDL_Point> circleCenters;
			for (size_t i = 0; i < circles.size(); i++)
			{
				circleCenters.push_back(circles[i].center);
			}

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