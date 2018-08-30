#include "GameBlock.h"

void GameBlock::setWidthAndHeight(int w, int h)
{
	this->w = w;
	this->h = h;
}

void GameBlock::update(float dt)
{
	//int posX = (this->pos.x - 60) % 20;
	if (this->pos.y - this->h < 400)
		updateMovement();
	else
		blockStopped = true;
}

void GameBlock::draw()
{
	SDL_Rect Rect = { pos.x, pos.y, w, h };
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	if (type == 0) // 'I', 4 stacks vertically
		SDL_SetRenderDrawColor(renderer, 120, 240, 240, 255);
	if (type == 1) // 'J', 3 stacks vertically & 1 left addition at most bottom
		SDL_SetRenderDrawColor(renderer, 120, 120, 240, 255);
	if (type == 2) // 'L', 3 stacks vertically & 1 right addition at most bottom
		SDL_SetRenderDrawColor(renderer, 240, 180, 120, 255);
	if (type == 3) // 'O', 2x2 stacks in a square
		SDL_SetRenderDrawColor(renderer, 240, 240, 120, 255);
	if (type == 4) // 'S', 2x2 stacks, the top blocks aligned to right by 1
		SDL_SetRenderDrawColor(renderer, 120, 240, 120, 255);
	if (type == 5) // 'Z', 2x2 stacks, the top blocks aligned to left by 1
		SDL_SetRenderDrawColor(renderer, 240, 120, 120, 255);
	if (type == 6) // 'T', 3 stacks horizontally & 1 top addition at middle
		SDL_SetRenderDrawColor(renderer, 240, 120, 240, 255);
	SDL_RenderFillRect(renderer, &Rect);
}