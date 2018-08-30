#pragma once
#include "GameObject.h"
class GamePanel :
	public GameObject
{
private:
	int w, h;
public:
	void setWidthAndHeight(int=18, int=18);
	virtual void draw();
};

