#pragma once
#include <SDL.h>
#include "Vector.h"
#include <string>

class GameObject
{
protected:
	SDL_Renderer* renderer;
public:
	Vector pos;
	Vector velocity;
	std::string objType;
	void setRenderer(SDL_Renderer* renderer);
	virtual void update(float dt);
	virtual void updateMovement();
	virtual void draw();
};

