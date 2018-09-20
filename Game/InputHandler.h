#pragma once
#include <SDL.h>
#include "GameBlocks.h"
#include "SoundManager.h"
class InputHandler :
	public GameBlock
{
public:
	GameBlocks* blocks;
	virtual void update(SDL_Event* event) = 0;
};

