#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <list>
#include <stdlib.h>
#include <time.h>
#include "GameObject.h"
#include "GamePanel.h"
#include "GameBlock.h"
#include "GameBlocks.h"
#include "KeyboardHandler.h"

using namespace std;

KeyboardHandler keyboardHandler;

GameBlocks currentBlocks;

void createBlock(list<GameObject*> &gameObjects, SDL_Renderer* renderer)
{
	//CREATE PLAYABLE BLOCK
	int typeM = rand() % 7;
	bool blockCreate = false;
	for (int i = 0; i < 4; i++)
	{
		GameBlock* block = new GameBlock();
		block->setType(typeM);
		block->setRenderer(renderer);
		block->setWidthAndHeight(20, 20);
		if (typeM == 0)
		{
			block->pos.x = 120 + (i * 20);
			block->pos.y = 40;
		}
		if (typeM == 1)
		{
			if (i == 0)
			{
				block->pos.x = 140;
				block->pos.y = 40;
			}
			if (i > 0)
			{
				block->pos.x = 120 + (i * 20);
				block->pos.y = 60;
			}
		}
		if (typeM == 2)
		{
			if (i == 0)
			{
				block->pos.x = 180;
				block->pos.y = 40;
			}
			if (i > 0)
			{
				block->pos.x = 120 + (i * 20);
				block->pos.y = 60;
			}
		}
		if (typeM == 3)
		{
			if (i < 2)
			{
				block->pos.x = 160 + (i * 20);
				block->pos.y = 40;
			}
			if (i >= 2)
			{
				block->pos.x = 120 + (i * 20);
				block->pos.y = 60;
			}
		}
		if (typeM == 4)
		{
			if (i < 2)
			{
				block->pos.x = 140 + (i * 20);
				block->pos.y = 60;
			}
			if (i >= 2)
			{
				block->pos.x = 120 + (i * 20);
				block->pos.y = 40;
			}
		}
		if (typeM == 5)
		{
			if (i < 2)
			{
				block->pos.x = 140 + (i * 20);
				block->pos.y = 40;
			}
			if (i >= 2)
			{
				block->pos.x = 120 + (i * 20);
				block->pos.y = 60;
			}
		}

		if (typeM == 6)
		{
			if (i == 0)
			{
				block->pos.x = 160;
				block->pos.y = 40;
			}
			if (i > 0)
			{
				block->pos.x = 120 + (i * 20);
				block->pos.y = 60;
			}
		}
		gameObjects.push_back(block);
		keyboardHandler.blocks = &currentBlocks;
		currentBlocks.blocks.push_back(block);
		if (block != NULL)
			blockCreate = true;
	}
	char typeC = 'I';
	if (typeM == 1)
		typeC = 'J';
	if (typeM == 2)
		typeC = 'L';
	if (typeM == 3)
		typeC = '0';
	if (typeM == 4)
		typeC = 'S';
	if (typeM == 5)
		typeC = 'Z';
	if (typeM == 6)
		typeC = 'T';
	if (blockCreate)
		cout << "Construction block " << typeC << " is created!" << endl;
	else
		cout << "Construction block failed!" << endl;
}

int main(int argc, char **argv)
{

	//sets seed value to use in rand function to change which random number set numbers come up
	srand(time(NULL));
	/*
	INITIALISE
		Do not forget to set Game's properties, Configuration Properties, 
		VC++ Directories, Include Directories (change SDL lib address "...\sdl2\include")
		VC++ Directories, Library Directories (change SDL lib address "...\sdl2\lib\x86")

		Linker, Input, Additional Dependencies (SDL2.lib, SDL2main.lib, SDL2_image.lib, SDL2_ttf.lib)
		Linker, System, SubSystem (CONSOLE or WINDOWS)
	*/
	//Initialise SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "SDL failed!" << endl;
		return -1;
	}
	else
		cout << "SDL initialised!" << endl;
	//Initialise SDL image
	if (!(IMG_Init(IMG_INIT_PNG)&IMG_INIT_PNG))
	{
		cout << "SDL image failed: " << IMG_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}
	else
		cout << "SDL image initialised!" << endl;
	/*
	//Initialise SDL mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
	{
		cout << "SDL mixer failed!" << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}
	else
		cout << "SDL mixer intialised!" << endl;
	*/
	//Create Window
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (window != NULL)
		cout << "Window created!" << endl;
	else
	{
		cout << "Window failed!" << endl;
		return -1;
	}
	//Initialise SDL ttf
	if (TTF_Init() != 0)
	{
		cout << "SDL ttf failed!" << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}
	else
		cout << "SDL ttf intialised!" << endl;
	//Create Renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer != NULL)
		cout << "Renderer created!" << endl;
	else
	{
		cout << "Renderer failed!" << endl;
		return -1;
	}
	list<GameObject*> gameObjects;
	//CREATE GAME PANELS FIELD
	/*
	Build GamePanels
	Field dimension 10x20sq
	Each square is 20x20px
	*/
	GamePanel *panels[20][10];
	int createPanels = 0;
	for (int i = 0; i < 20; i++)
	{
		for (int ii = 0; ii < 10; ii++)
		{
			GamePanel* panel = new GamePanel();
			panel->setRenderer(renderer);
			panel->setWidthAndHeight();
			panel->pos.x = (ii * 20) + 60 + 1;
			panel->pos.y = 420 - (i * 20) + 1;
			panel->setOccupy(false);
			if (panel != NULL)
				createPanels++;
			panels[i][ii] = panel;
			//gameObjects.push_back(panel); 
		}
	}
	cout <<createPanels << " out of 200 panel(s) created!" << endl;
	//MAIN GAME LOOP
	createBlock(gameObjects, renderer);
	Uint32 lastUpdate = SDL_GetTicks();
	int currentFrame = 0;
	float frameTimer = 0.1; //Supposedly 0.083
	int delay1 = 5;
	int delay2 = 60;
	int delayC = 0;
	bool loop = true;
	while (loop)
	{
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		float dt = timeDiff / 1000.0;
		lastUpdate = SDL_GetTicks();
		SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
		SDL_RenderClear(renderer);
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				loop = false;
			if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
					loop = false;
			keyboardHandler.update(&event);
		}
		if (delayC%delay2 == 0)
		{
			currentBlocks.moveDown();
			for each (GameBlock* b1 in currentBlocks.blocks)
				for each (GameBlock* b2 in gameObjects)
					if(b1->pos.y+20 == b2->pos.y && b1->pos.x == b2->pos.x && b2->blockStopped)
						b1->blockStopped = true;
			/*
			currentBlocks.stopAllCurrentBlocks??
			makenewBlock = true;
			*/
			/*for (GameObject* go : gameObjects){
				if (go->objType == "block"){
					GameBlock* b = (GameBlock*)go;

					b->pos.x = 2323423424;
				}
			}*/
		}
		for each (GamePanel* p in panels)
			p->draw();
		bool makeNewBlock = true;
		for each (GameObject* go in gameObjects)
		{
			go->update(dt);
			go->draw();
			if (go->objType == "block")
			{
				//Cast game object to try reference as game block
				GameBlock* blockref = (GameBlock*)go;
				if (!blockref->blockStopped)
					makeNewBlock = false;
			}
		}
		if (makeNewBlock)
		{
			//Fill in occupies
			/*
			for (GameBlock* b : currentBlocks.blocks)
				for (int i = 0; i < 20; i++)
					for (int ii = 0; ii < 10; ii++)
						if (b->pos.x == panels[i][ii]->pos.x - 1 && b->pos.y == panels[i][ii]->pos.y - 1)
							panels[i][ii]->setOccupy(true);
			*/
			/*
			//To check whether the line is filled in to be deleted or not
			cout << "Bottom Panel check : ";
			for (int i = 0; i < 10; i++)
				cout << panels[0][i]->getOccupy() << " ";
			cout << endl;
			*/
			for (int i = 0; i < 20; i++)
			{
				bool deleteLine = true;
				for (GameBlock* b : currentBlocks.blocks)
					for (int ii = 0; ii < 10; ii++)
						if (b->pos.x == panels[i][ii]->pos.x - 1 && b->pos.y == panels[i][ii]->pos.y - 1)
							panels[i][ii]->setOccupy(true);
				for (int ii = 0; ii < 10; ii++)
					if (panels[i][ii]->getOccupy() == false)
						deleteLine = false;
				if (deleteLine)
				{
					for (list<GameObject*>::iterator goIt = gameObjects.begin(); goIt != gameObjects.end();)//when deleting, do put goIt++ here
					{
						if ((*goIt)->pos.y == panels[i][0]->pos.y -1)
						{
							delete (*goIt); //delete dynamically allocated block
							goIt = gameObjects.erase(goIt); //remove block pointer from list
						}
						else
							goIt++;
					}

					//Drop commmand;
					//TODO move all blocks in gameObjects down by1
					/*
					for each (GameBlock* b in gameObjects)
						b.moveDown();
					*/

					for (int ii = 0; ii < 10; ii++)
						panels[i][ii]->setOccupy(false);
				}
			}
			currentBlocks.blocks.clear();
			createBlock(gameObjects, renderer);//Create new block
		}
		SDL_RenderPresent(renderer);
		delayC++;
	}
	//CLEANING UP
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	system("pause");
	return 0;
}