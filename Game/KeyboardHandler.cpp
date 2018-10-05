#include "KeyboardHandler.h"

void KeyboardHandler::update(SDL_Event* event)
{
	const Uint8* keystates = SDL_GetKeyboardState(NULL);
	if (keystates[SDL_SCANCODE_DOWN]){
		blocks->moveDown();
		SoundManager::soundManager.playSound("move1");
	}
	if (keystates[SDL_SCANCODE_LEFT] && blocks->mostLeftBlock() - 20 > 0)
		blocks->moveLeft();
	if (keystates[SDL_SCANCODE_RIGHT] && blocks->mostRightBlock() + 20 < 220)
		blocks->moveRight();
}
