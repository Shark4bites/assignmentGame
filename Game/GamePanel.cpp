#include "GamePanel.h"

void GamePanel::setWidthAndHeight(int w, int h)
{
	this->w = w;
	this->h = h;
}

void GamePanel::draw()
{
	SDL_Rect Rect = { pos.x, pos.y, w, h };
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &Rect);
}

void GamePanel::setOccupy(bool b)
{
	this->occupied = b;
}

bool GamePanel::getOccupy()
{
	return occupied;
}