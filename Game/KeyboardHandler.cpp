#include "KeyboardHandler.h"

void KeyboardHandler::update(SDL_Event* event)
{
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	block->velocity.x = 0;
	block->velocity.y = 0;
	if (keystates[SDL_SCANCODE_DOWN])
		block->velocity.y = 20;
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.scancode == SDL_SCANCODE_LEFT && event->key.repeat == 0 && block->pos.x - 20 > 40)
			block->velocity.x = -20;
		if (event->key.keysym.scancode == SDL_SCANCODE_RIGHT && event->key.repeat == 0 && block->pos.x + 20 < 260)
			block->velocity.x = 20;
	}
}
