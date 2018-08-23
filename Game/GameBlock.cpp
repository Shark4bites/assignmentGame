#include "GameBlock.h"
#include <ctype.h>

void GameBlock::setWidthAndHeight(int w, int h)
{
	this->w = w;
	this->h = h;
}

void GameBlock::update(float dt)
{
	if (pos.x - w> borderL && pos.x + w< borderR && pos.y< borderD)
		updateMovement();
}

void GameBlock::draw()
{
	SDL_Rect Rect = { pos.x, pos.y, w, h };
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	if(islower(type))
		toupper(type);
	if (type == 'I')
		SDL_SetRenderDrawColor(renderer, 120, 240, 240, 255);
	if (type == 'J')
		SDL_SetRenderDrawColor(renderer, 120, 120, 240, 255);
	if (type == 'L')
		SDL_SetRenderDrawColor(renderer, 240, 180, 120, 255);
	if (type == 'O')
		SDL_SetRenderDrawColor(renderer, 240, 240, 120, 255);
	if (type == 'S')
		SDL_SetRenderDrawColor(renderer, 120, 240, 120, 255);
	if (type == 'T')
		SDL_SetRenderDrawColor(renderer, 240, 120, 240, 255);
	if (type == 'Z')
		SDL_SetRenderDrawColor(renderer, 240, 120, 120, 255);
	SDL_RenderFillRect(renderer, &Rect);
}