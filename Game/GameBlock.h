#pragma once
#include "GameObject.h"
#include <stdlib.h>
class GameBlock :
	public GameObject
{
private:
	int w, h;
	
public:
	GameBlock()
	{
		objType = "block";
	}
	void setWidthAndHeight(int w, int h);
	virtual void update(float dt);
	virtual void draw();
	int type = rand() % 7;
	bool blockStopped = false;
};

