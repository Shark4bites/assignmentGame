#pragma once
#include "GameObject.h"
class GamePanel :
	public GameObject
{
private:
	int w, h;
	bool occupied = false;
public:
	void setWidthAndHeight(int=18, int=18);
	virtual void draw();
	void setOccupy(bool);
	bool getOccupy();
};

