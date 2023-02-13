#include <iostream>
#include <vector>
#include "EventHandler.h"

void EventHandler(SDL_Event& e, bool& running, std::vector<Circle>& circles, SDL_Point& mousePos, int& radiusSetting)
{
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
}
