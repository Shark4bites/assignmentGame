#pragma once
#include <SDL.h>
#include "Vector.h"

class GameObject
{
protected:
	SDL_Renderer* renderer;
public:
	Vector pos;
	Vector velocity;
	int borderL = 0;
	int borderR = 640;
	int borderU = 0;
	int borderD = 480;
	void setRenderer(SDL_Renderer* renderer);
	virtual void update(float dt);
	virtual void updateMovement();
	virtual void draw();
};

