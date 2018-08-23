#pragma once
#include <SDL.h>
#include "GameBlock.h"
class InputHandler :
	public GameBlock
{
public:
	GameBlock* block;
	virtual void update(SDL_Event* event) = 0;
};

