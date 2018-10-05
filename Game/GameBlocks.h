#pragma once
#include "GameObject.h"
#include "GameBlock.h"
#include<list>

//manages a group of blocks (e.g L shape group has 4 blocks)

class GameBlocks 
{
public:
	std::list<GameBlock*> blocks;
	void moveLeft();
	void moveRight();
	void moveDown(); 
	float mostLeftBlock();
	float mostRightBlock();

	void rotateRight();
	void rotateLeft();
};

