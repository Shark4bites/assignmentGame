#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <list>
#include <stdlib.h>
#include "GameObject.h"
#include "GamePanel.h"
#include "GameBlock.h"
#include "GameBlocks.h"
#include "KeyboardHandler.h"

using namespace std;

KeyboardHandler keyboardHandler;

GameBlock* currentBlock;

void createBlock(list<GameObject*> &gameObjects, SDL_Renderer* renderer){
	//CREATE PLAYABLE BLOCK
	GameBlock* block = new GameBlock();
	block->setRenderer(renderer);
	block->setWidthAndHeight(20, 20);
	block->pos.x = 160;
	block->pos.y = 40;
	gameObjects.push_back(block);

	keyboardHandler.block = block;
	currentBlock = block;
	if (block != NULL)
		cout << "Controllable block created!" << endl;
	else
		cout << "Controllable block failed!" << endl;
}

int main(int argc, char **argv)
{
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
		cout << "SDL image loaded!" << endl;
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
	for (int i = 0; i < 20; i++)
		for (int ii = 0; ii < 10; ii++)
			panels[i][ii] = false;
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
	int delay2 = 10;
	int delayC = 0;
	bool loop = true;
	while (loop)
	{
		Uint32 timeDiff = SDL_GetTicks() - lastUpdate;
		float dt = timeDiff / 1000.0;
		lastUpdate = SDL_GetTicks();
		SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
		SDL_RenderClear(renderer);
		if (delayC%delay1 == 0)
		{
			if (delayC%delay2 == 0){ currentBlock->velocity.y = 20; }
			SDL_Event event;
			while (SDL_PollEvent(&event))
			{
				if (event.type == SDL_QUIT)
					loop = false;
				if (event.type == SDL_KEYDOWN)
					if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
						loop = false;
					else
						;
				else
					keyboardHandler.update(&event);
			}
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
			createBlock(gameObjects, renderer);//Create new block
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