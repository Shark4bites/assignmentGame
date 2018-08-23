#pragma once
#include "GameObject.h"
class GameBlock :
	public GameObject
{
private:
	int w, h;
public:
	void setWidthAndHeight(int w, int h);
	virtual void update(float dt);
	virtual void draw();
	char type;
	int borderL = 40;
	int borderR = 260;
	int borderU = 60;
	int borderD = 420;
};

