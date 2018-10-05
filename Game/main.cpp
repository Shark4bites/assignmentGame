#include <iostream>
#include <fstream>
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
#include "SoundManager.h"

using namespace std;

KeyboardHandler keyboardHandler;

GameBlocks currentBlocks;

int currTypeC1 = -1;
int currTypeC2 = -2;
int currTypeF = -1;

int diff = 0;

int score = 0;

void createBlock(list<GameObject*> &gameObjects, SDL_Renderer* renderer)
{
	//CREATE PLAYABLE BLOCK

	//Randomizer
	int randType = 4;
	if (diff > 1)
		randType = 7;
	int typeC = rand() % randType; // The type of blocks colo
	//To ensure RNG does not repeat the 2 previous
	while (typeC == currTypeC1 || typeC == currTypeC2)
	{
		typeC = rand() % randType;
		if (typeC != currTypeC1 && typeC != currTypeC2)
			break;
	}

	//Randomizer
	int randForm = 2;
	if (diff == 3)
		randForm = 4;
	int typeF = rand() % randForm; // The type of blocks formation
	//To ensure RNG does not repeat the 1 previous
	while (typeF == currTypeF)
	{
		typeF = rand() % randForm;
		if (typeF != currTypeF)
			break;
	}
	bool blockCreate = false;
	for (int i = 0; i < 4; i++)
	{
		GameBlock* block = new GameBlock();
		block->setType(typeC);
		block->setRenderer(renderer);
		block->setWidthAndHeight(20, 20);
		block->setForm(i, typeF);
		gameObjects.push_back(block);
		keyboardHandler.blocks = &currentBlocks;
		currentBlocks.blocks.push_back(block);
		if (block != NULL)
			blockCreate = true;
	}
	currTypeC2 = currTypeC1;
	currTypeC1 = typeC;
	currTypeF = typeF;
	/*
	if (blockCreate)
	cout << "Block is spawned!" << endl;
	else
	cout << "Block failed!" << endl;
	*/
}

int main(int argc, char **argv)
{
	//sets seed value to use in rand function to change which random number set numbers come up
	srand(time(NULL));

	/*
	INITIALISE
		Do not forget to set Game's properties, Configuration Properties, 
		VC++ Directories, directories of the SDL lib
		VC++ Directories, Include Directories (change SDL lib address "...\sdl2\include")
		VC++ Directories, Library Directories (change SDL lib address "...\sdl2\lib\x86")

		Linker, Input, Additional Dependencies (SDL2.lib, SDL2main.lib, SDL2_image.lib, SDL2_ttf.lib, SDL2_mixer.lib)
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
	
	//Create Window
	SDL_Window* window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 240, 440, SDL_WINDOW_SHOWN);
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
			panel->pos.x = (ii * 20) + 21;
			panel->pos.y = 380 - (i * 20) + 21;
			panel->setOccupy(false);
			if (panel != NULL)
				createPanels++;
			panels[i][ii] = panel;
		}
	}
	cout <<createPanels << " out of 200 panel(s) created!" << endl;

	//MUSIC
	Mix_Music* music = Mix_LoadMUS("Assets/bgm.ogg");
	if (music == NULL)
	{
		cout << "Music failed to load! " << Mix_GetError() << endl;
		SDL_Quit();
		system("pause");
		return -1;
	}
	else
		cout << "Music loaded!" << endl;
	SoundManager::soundManager.loadSound("move1", "Assets/move1.wav");
	SoundManager::soundManager.loadSound("move2", "Assets/move2.wav");

	//LOAD FONT
	SDL_Color textcolour = { 240, 240, 240, 255 };

	TTF_Font* font0 = TTF_OpenFont("Assets/Inconsolata-Bold.ttf", 30);
	SDL_Surface* textSurface0 = TTF_RenderText_Blended(font0, "STACKZ", textcolour);
	SDL_Texture* textTexture0 = SDL_CreateTextureFromSurface(renderer, textSurface0);
	SDL_FreeSurface(textSurface0);
	SDL_Rect textDestination0;
	textDestination0.x = 80;
	textDestination0.y = 50;
	SDL_QueryTexture(textTexture0, NULL, NULL, &textDestination0.w, &textDestination0.h);

	TTF_Font* font1 = TTF_OpenFont("Assets/Inconsolata-Bold.ttf", 20);
	SDL_Surface* textSurface1 = TTF_RenderText_Blended(font1, "Select Difficulty", textcolour);
	SDL_Texture* textTexture1 = SDL_CreateTextureFromSurface(renderer, textSurface1);
	SDL_FreeSurface(textSurface1);
	SDL_Rect textDestination1;
	textDestination1.x = 40;
	textDestination1.y = 90;
	SDL_QueryTexture(textTexture1, NULL, NULL, &textDestination1.w, &textDestination1.h);

	TTF_Font* font2 = TTF_OpenFont("Assets/Inconsolata-Regular.ttf", 15);
	SDL_Surface* textSurface2 = TTF_RenderText_Blended(font2, "1 EASY 2 NORMAL 3 HARD", textcolour);
	SDL_Texture* textTexture2 = SDL_CreateTextureFromSurface(renderer, textSurface2);
	SDL_FreeSurface(textSurface2);
	SDL_Rect textDestination2;
	textDestination2.x = 30;
	textDestination2.y = 120;
	SDL_QueryTexture(textTexture2, NULL, NULL, &textDestination2.w, &textDestination2.h);

	SDL_Surface* textSurface3 = TTF_RenderText_Blended(font2, "Esc for Quit", textcolour);
	SDL_Texture* textTexture3 = SDL_CreateTextureFromSurface(renderer, textSurface3);
	SDL_FreeSurface(textSurface3);
	SDL_Rect textDestination3;
	textDestination3.x = 70;
	textDestination3.y = 140;
	SDL_QueryTexture(textTexture3, NULL, NULL, &textDestination3.w, &textDestination3.h);

	//MENU-MAIN GAME LOOP
	createBlock(gameObjects, renderer);
	Uint32 lastUpdate = SDL_GetTicks();
	int currentFrame = 0;
	float frameTimer = 0.1; //Supposedly 0.083
	bool menu = true;
	bool loop = true;
	while (menu)
	{
		SDL_SetRenderDrawColor(renderer, 120, 120, 120, 255);
		SDL_RenderClear(renderer);
		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				loop = false;
				menu = false;
			}
			if (event.type == SDL_KEYDOWN)
				if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				{
					loop = false;
					menu = false;
				}
				else if (event.key.keysym.scancode >= 30 && event.key.keysym.scancode <= 32)
				{
					menu = false;
					diff = event.key.keysym.scancode - 29;
				}
		}
		SDL_RenderCopy(renderer, textTexture0, NULL, &textDestination0);
		SDL_RenderCopy(renderer, textTexture1, NULL, &textDestination1);
		SDL_RenderCopy(renderer, textTexture2, NULL, &textDestination2);
		SDL_RenderCopy(renderer, textTexture3, NULL, &textDestination3);
		SDL_RenderPresent(renderer);
	}
	if (diff >= 1 && diff <= 3)
	{
		Mix_PlayMusic(music, -1);
		cout << "You have selected a difficulty, it's ";
		if (diff == 1)
			cout << "EASY\n";
		if (diff == 2)
			cout << "NORMAL\n";
		if (diff == 3)
			cout << "HARD\n";
	}

	SDL_DestroyTexture(textTexture0);
	SDL_DestroyTexture(textTexture1);
	SDL_DestroyTexture(textTexture2);
	SDL_DestroyTexture(textTexture3);

	int delay1 = 5;
	int delay2 = 60;
	int delayC = 0;
	
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
			SoundManager::soundManager.playSound("move2");
			currentBlocks.moveDown();
		}

		bool stopAllCurrentBlocks = false;
		for each (GameBlock* b1 in currentBlocks.blocks)
			for each (GameBlock* b2 in gameObjects)
				if (b1->pos.y + 20 == b2->pos.y && b1->pos.x == b2->pos.x && b2->blockStopped)
				{
					stopAllCurrentBlocks = true;
					break;
				}
		if (stopAllCurrentBlocks)
			for each (GameBlock* b1 in gameObjects)
				b1->blockStopped = true;

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
				else if (blockref->pos.y == 60)
				{
					makeNewBlock = false;
					loop = false;
					//GAME OVER
				}
			}
		}
		
		if (makeNewBlock)
		{
			for (int i = 0; i < 20; i++)
				for (int ii = 0; ii < 10; ii++)
					panels[i][ii]->setOccupy(false);

			for (int i = 0; i < 20; i++)
			{
				bool deleteLine = true;
				while (deleteLine == true)
				{
					//Checking All blocks
					int c = 0;
					for (list<GameObject*>::iterator goIt = gameObjects.begin(); goIt != gameObjects.end(); goIt++)
						if ((*goIt)->objType == "block")
						{
							GameBlock* b = (GameBlock*)(*goIt);
							for (int ii = 0; ii < 10; ii++)
								if (b->pos.x == panels[i][ii]->pos.x - 1 && b->pos.y == panels[i][ii]->pos.y - 1)
								{
									panels[i][ii]->setOccupy(true);
									break;
								}
						}
					for (int ii = 0; ii < 10; ii++)
						if (panels[i][ii]->getOccupy() == false)
							deleteLine = false;

					if (deleteLine)
					{
						int scoreAdd = 100 * diff;
						for (list<GameObject*>::iterator goIt = gameObjects.begin(); goIt != gameObjects.end();)//when deleting, do put goIt++ here
						{
							if ((*goIt)->pos.y == panels[i][0]->pos.y - 1)
							{
								score += scoreAdd;
								delete (*goIt); //delete dynamically allocated block
								goIt = gameObjects.erase(goIt); //remove block pointer from list
							}
							else
								goIt++;
							scoreAdd += 100 * diff;
						}

						for (list<GameObject*>::iterator goIt = gameObjects.begin(); goIt != gameObjects.end(); goIt++)
						{
							//when not deleting, do put goIt++ here
							if ((*goIt)->objType == "block" && (*goIt)->pos.y < panels[i][0]->pos.y - 1)
							{
								GameBlock* blockref = (GameBlock*)(*goIt);
								int iX = ((blockref->pos.x - 20) / 20) - 1;
								int iY = 19 - ((blockref->pos.y - 20) / 20);
								blockref->velocity.y = 20;
								blockref->blockStopped = false;
							}
						}
						for (int ii = 0; ii < 10; ii++)
							panels[i][ii]->setOccupy(false);
						deleteLine = true;
					}
				}
			}

			for (int i = 0; i < 20; i++)
				for (list<GameObject*>::iterator goIt = gameObjects.begin(); goIt != gameObjects.end(); goIt++)
					if ((*goIt)->objType == "block")
					{
						GameBlock* b = (GameBlock*)(*goIt);
						for (int ii = 0; ii < 10; ii++)
							if (b->pos.x == panels[i][ii]->pos.x - 1 && b->pos.y == panels[i][ii]->pos.y - 1)
							{
								panels[i][ii]->setOccupy(true);
								break;
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

	cout << "Your score is : " << score << endl;
	cout << "The high score is : ";
	//string line;
	int fileScore;
	ifstream myfile("score.txt");
	if (myfile.is_open())
	{
		myfile >> fileScore; // Read into fileScore
		myfile.close();
		if (score > fileScore)
		{
			ofstream myfile("score.txt");
			if (myfile.is_open())
			{
				myfile << score; //Write in the score
				cout << score << endl;
				myfile.close();
			}
		}
		else
			cout << fileScore << endl; 
	}
	else
	{
		cout << score;
		cout << "Unable to be compared with previous score(s).\n";
	}

	system("pause");
	return 0;
}