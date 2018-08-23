#pragma once
#include "InputHandler.h"
class KeyboardHandler :
	public InputHandler
{
public:
	void update(SDL_Event* event);
};

