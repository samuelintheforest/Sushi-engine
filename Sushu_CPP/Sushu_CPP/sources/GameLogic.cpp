#include "../includes/GameLogic.h"

sushi::Timer* sushi::GameLogic::TimerManager = 0;
sushi::Display* sushi::GameLogic::DisplayManager = 0;
sushi::Input* sushi::GameLogic::InputManager = 0;
sushi::Graphics* sushi::GameLogic::GraphicsManager = 0;

void sushi::GameLogic::initGame(void)
{
	sushi::GameLogic::TimerManager = new sushi::Timer();
	sushi::GameLogic::DisplayManager = new sushi::Display(800, 800, false, true);
	sushi::GameLogic::InputManager = new sushi::Input(DisplayManager);
	sushi::GameLogic::GraphicsManager = new sushi::Graphics();
	
}

void sushi::GameLogic::endGame(void)
{
	delete sushi::GameLogic::DisplayManager;
	delete sushi::GameLogic::InputManager;
	delete sushi::GameLogic::GraphicsManager;
	delete sushi::GameLogic::TimerManager;
}

void sushi::GameLogic::updateState()
{
	/* Update the input events */
	sushi::GameLogic::InputManager->pollEvents();
}


