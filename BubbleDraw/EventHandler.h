#pragma once
#include <SDL.h>
#include "Structs/primitiveStructs.h"

void EventHandler(SDL_Event& e, bool& running, std::vector<Circle>& circles, SDL_Point& mousePos, int& radiusSetting);