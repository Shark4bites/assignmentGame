#include "GameControllerHandler.h"
GameControllerHandler::GameControllerHandler()
{
	int numJoysticks = SDL_NumJoysticks();
	for (int joystickID = 0; joystickID < numJoysticks; joystickID++)
	{
		if (SDL_IsGameController(joystickID))
		{
			controller = SDL_GameControllerOpen(joystickID);
			break;
		}
	}
}
GameControllerHandler::~GameControllerHandler()
{
	if (controller != NULL)
		SDL_GameControllerClose(controller);
}
void GameControllerHandler::update(SDL_Event* event)
{
	if (controller != NULL && SDL_GameControllerGetAttached(controller))
	{
		SDL_JoystickID joystickID = SDL_JoystickInstanceID(SDL_GameControllerGetJoystick(controller));
		if (event->cdevice.which == joystickID)
		{
			if (event->type == SDL_CONTROLLERDEVICEREMOVED)
			{
				SDL_GameControllerClose(controller);
				controller = NULL;
				return;
			}
			block->velocity.x = 0;
			block->velocity.y = 0;
			Sint16 axisX = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTX);
			Sint16 axisY = SDL_GameControllerGetAxis(controller, SDL_CONTROLLER_AXIS_LEFTY);
			int deadzone = 10000;
			if (axisX < -deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_LEFT))
				block->velocity.x = -2000;
			if (axisX > deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_RIGHT))
				block->velocity.x = 2000;
			if (axisY > deadzone || SDL_GameControllerGetButton(controller, SDL_CONTROLLER_BUTTON_DPAD_DOWN))
				block->velocity.y = 2000;

		}
	}
}