#include "KeyboardHandler.h"

void KeyboardHandler::update(SDL_Event* event)
{
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	block->velocity.x = 0;
	block->velocity.y = 0;
	if (keystates[SDL_SCANCODE_DOWN])
		block->velocity.y = 20;
	if (keystates[SDL_SCANCODE_LEFT] && block->pos.x - 20 > 40)
		block->velocity.x = -20;
	if (keystates[SDL_SCANCODE_RIGHT] && block->pos.x + 20 < 260)
		block->velocity.x = 20;
}
