#include "GameObject.h"

void GameObject::setRenderer(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void GameObject::update(float dt)
{
}

void GameObject::updateMovement()
{
	pos.x = pos.x + velocity.x;
	pos.y = pos.y + velocity.y;
	velocity.x = 0;
	velocity.y = 0;
}

void GameObject::draw()
{
}