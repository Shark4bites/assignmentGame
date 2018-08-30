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
	int borderL = 40;
	int borderR = 260;
	int borderU = -20; //60;
	int borderD = 400;
	int type;
	bool blockStopped = false;
};

