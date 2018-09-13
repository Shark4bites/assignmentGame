#include "GameBlocks.h"


void GameBlocks::moveLeft()
{
	for (GameBlock* block : blocks)
		block->velocity.x = -20;
}
void GameBlocks::moveRight()
{
	for (GameBlock* block : blocks)
		block->velocity.x = 20;
}
void GameBlocks::moveDown()
{
	for (GameBlock* block : blocks)
		block->velocity.y = 20;
}

float GameBlocks::mostLeftBlock()
{
	float leftX = blocks.front()->pos.x;
	for (GameBlock* block : blocks)
		if (block->pos.x < leftX)
			leftX = block->pos.x;
	return leftX;
}

float GameBlocks::mostRightBlock()
{
	float rightX = blocks.front()->pos.x;
	for (GameBlock* block : blocks)
		if (block->pos.x > rightX)
			rightX = block->pos.x;
	return rightX;
}