#pragma once
#include "GameObject.h"
#include "GameBlock.h"
#include<list>

//manages a group of blocks (e.g L shape group has 4 blocks)

class GameBlocks 
{
public:
	std::list<GameBlock*> blocks;
	//virtual void update();
	//virtual void draw();
	void moveLeft();
	void moveRight();
	void moveDown(); 
	float mostLeftBlock();
	float mostRightBlock();

	//override update function to update alllllll blocks in group at once to move

	//override draw function to loop through and draw all blocks in group
};

