#pragma once
#include "GameObject.h"
class GamePanel :
	public GameObject
{
private:
	int w, h;
public:
	void setWidthAndHeight(int=19, int=19);
	virtual void draw();
};

