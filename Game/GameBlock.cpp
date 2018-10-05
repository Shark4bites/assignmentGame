#include "GameBlock.h"

void GameBlock::setWidthAndHeight(int w, int h)
{
	this->w = w;
	this->h = h;
}

void GameBlock::update(float dt)
{
	if (!blockStopped && this->pos.y - this->h < 380)
		updateMovement();
	else
		blockStopped = true;
}

void GameBlock::setType(int t)
{
	if (t > 0 && t < 7)
		this->type = t;
}

void GameBlock::draw()
{
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	if (type == 0) // 'I', 4 stacks vertically
		SDL_SetRenderDrawColor(renderer, 120, 240, 240, 255); // Cyan
	if (type == 1) // 'J', 3 stacks vertically & 1 left addition at most bottom
		SDL_SetRenderDrawColor(renderer, 120, 120, 240, 255); // Blue
	if (type == 2) // 'L', 3 stacks vertically & 1 right addition at most bottom
		SDL_SetRenderDrawColor(renderer, 240, 180, 120, 255); // Orange
	if (type == 3) // 'O', 2x2 stacks in a square
		SDL_SetRenderDrawColor(renderer, 240, 240, 120, 255); // Yellow
	if (type == 4) // 'S', 2x2 stacks, the top blocks aligned to right by 1
		SDL_SetRenderDrawColor(renderer, 120, 240, 120, 255); // Green
	if (type == 5) // 'Z', 2x2 stacks, the top blocks aligned to left by 1
		SDL_SetRenderDrawColor(renderer, 240, 120, 120, 255); // Red
	if (type == 6) // 'T', 3 stacks horizontally & 1 top addition at middle
		SDL_SetRenderDrawColor(renderer, 240, 120, 240, 255); // Purple

	SDL_Rect Rect = { pos.x, pos.y, w, h };
	SDL_RenderFillRect(renderer, &Rect);
}

void GameBlock::setForm(int a, int f)
{
	int t = this->type;
	int x = 100;
	int y = 20;
	if (t > 0)
	{
		x += 20;
		if (t == 3)
			x += 20;
	}
	this->pos.x = x;
	this->pos.y = y;
	if (t == 0)
	{
		//|o|o|o|o|
		if (f > 1)
			this->pos.x = x + a * 20;
		//|o|
		//|o|
		//|o|
		//|o|
		else
		{
			this->pos.y = y + a * 20;
			this->pos.x = x + 40;
		}
	}
	if (t == 1)
	{
		if (f == 0)
		{
			//|o|
			//|o|o|o| 
			if (a < 3)
			{
				this->pos.y = y + 20;
				this->pos.x = x + a * 20;
			}
		}
		if (f == 2)
		{
			//|o|o|
			//|o|
			//|o|
			if (a < 3)
				this->pos.y = y + a * 20;
			else
				this->pos.x = x + 20;
		}
		if (f == 3)
		{
			//|o|o|o|
			//    |o|
			if (a < 3)
				this->pos.x = x + a * 20;
			else
			{
				this->pos.y = y + 20;
				this->pos.x = x + (a-1) * 20;
			}
		}
		if (f == 1)
		{
			//  |o|
			//  |o|
			//|o|o|
			if (a < 3)
			{
				this->pos.x = x + 20;
				this->pos.y = y + a * 20;
			}
			else
				this->pos.y = y + (a-1) * 20;
		}
	}
	if (t == 2)
	{
		if (f == 0)
		{
			//    |o|
			//|o|o|o| 
			if (a < 3)
			{
				this->pos.y = y + 20;
				this->pos.x = x + a * 20;
			}
			else
				this->pos.x = x + (a - 1) * 20;
		}
		if (f == 3)
		{
			//|o|o|
			//  |o|
			//  |o|
			if (a < 3)
				this->pos.y = y + a * 20;
			else
				this->pos.x = x - 20;
		}
		if (f == 2)
		{
			//|o|o|o|
			//|o|
			if (a < 3)
				this->pos.x = x + a * 20;
			else
				this->pos.y = y + 20;
		}
		if (f == 1)
		{
			//|o|
			//|o|
			//|o|o|
			if (a < 3)
				this->pos.y = y + a * 20;
			else
			{
				this->pos.x = x + 20;
				this->pos.y = y + (a - 1) * 20;
			}
		}
	}
	if (t == 3)
	{
		//|o|o|
		//|o|o|
		if (a < 2)
			this->pos.x = x + a * 20;
		else
		{
			this->pos.x = x + (a - 2) * 20;
			this->pos.y = y + 20;
		}
	}
	if (t == 4)
	{
		//  |o|o|
		//|o|o|
		if (f > 1)
		{
			if (a < 2)
				this->pos.x = x + (a + 1) * 20;
			else
			{
				this->pos.x = x + (a - 2) * 20;
				this->pos.y = y + 20;
			}
		}
		//|o|
		//|o|o|
		//  |o|
		else
		{
			if (a < 2)
				this->pos.y = y + a * 20;
			else
			{
				this->pos.x = x + 20;
				this->pos.y = y + (a-1) * 20;
			}
		}
	}
	if (t == 5)
	{
		//|o|o|
		//  |o|o|
		if (f > 1)
		{
			if (a < 2)
				this->pos.x = x + a * 20;
			else
			{
				this->pos.x = x + (a - 1) * 20;
				this->pos.y = y + 20;
			}
		}
		//  |o|
		//|o|o|
		//|o|
		else
		{
			if (a < 2)
			{
				this->pos.y = y + a * 20;
				this->pos.x = x + 20;
			}
			else
				this->pos.y = y + (a - 1) * 20;
		}
	}
	if (t == 6)
	{
		//  |o|
		//|o|o|o|
		if (f == 0)
		{
			if (a < 3)
			{

				this->pos.x = x + a * 20;
				this->pos.y = y + 20;
			}
			else
				this->pos.x = x + 20;
		}
		//|o|
		//|o|o|
		//|o|
		if (f == 2)
		{
			if (a < 3)
				this->pos.y = y + a * 20;
			else
			{
				this->pos.y = y + 20;
				this->pos.x = x + 20;
			}
		}
		//|o|o|o|
		//  |o|
		if (f == 1)
		{
			if (a < 3)
				this->pos.x = x + a * 20;
			else
			{
				this->pos.y = y + 20;
				this->pos.x = x + 20;
			}
		}
		//  |o|
		//|o|o|
		//  |o|
		if (f == 3)
		{
			if (a < 3)
			{
				this->pos.y = y + a * 20;
				this->pos.x = x + 20;
			}
			else
				this->pos.y = y + 20;
		}
	}
}