#include "../includes/GameLogic.h"

sushi::Display* sushi::GameLogic::DisplayManager = NULL;
sushi::Input* sushi::GameLogic::InputManager = NULL;
sushi::Graphics* sushi::GameLogic::GraphicsManager = NULL;

void sushi::GameLogic::initGame(void)
{
	DisplayManager = new sushi::Display(800, 800, false, true);
	InputManager = new sushi::Input(DisplayManager);
	GraphicsManager = new sushi::Graphics();
	
}

void sushi::GameLogic::endGame(void)
{
	delete DisplayManager;
	delete InputManager;
	delete GraphicsManager;
}
