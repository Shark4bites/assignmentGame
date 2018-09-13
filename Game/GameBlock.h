#pragma once
#include "GameObject.h"
#include <stdlib.h>
class GameBlock :
	public GameObject
{
private:
	int w, h;
	int type = 0;
	
public:
	GameBlock()
	{
		objType = "block";
	}
	void setWidthAndHeight(int w, int h);
	virtual void update(float dt);
	virtual void draw();
	bool blockStopped = false;
	void setType(int);
};

