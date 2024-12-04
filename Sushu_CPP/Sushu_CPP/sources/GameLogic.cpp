#include "../includes/GameLogic.h"

sushi::Timer* sushi::GameLogic::TimerManager = 0;
sushi::Display* sushi::GameLogic::DisplayManager = 0;
sushi::Input* sushi::GameLogic::InputManager = 0;
sushi::Graphics* sushi::GameLogic::GraphicsManager = 0;

void sushi::GameLogic::initGame(void)
{
	TimerManager = new sushi::Timer();
	DisplayManager = new sushi::Display(800, 800, false, true);
	InputManager = new sushi::Input(DisplayManager);
	GraphicsManager = new sushi::Graphics();
	
}

void sushi::GameLogic::endGame(void)
{
	delete DisplayManager;
	delete InputManager;
	delete GraphicsManager;
	delete TimerManager;
}


