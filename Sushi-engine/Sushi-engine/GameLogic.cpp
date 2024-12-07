#include "GameLogic.h"

sushi::Timer* sushi::GameLogic::TimerManager = 0;
sushi::Display* sushi::GameLogic::DisplayManager = 0;
sushi::Input* sushi::GameLogic::InputManager = 0;
sushi::Graphics* sushi::GameLogic::GraphicsManager = 0;
sushi::Scene* sushi::GameLogic::GameScene = 0;
uint64_t sushi::GameLogic::cycleStart = 0;

void sushi::GameLogic::initGame(void)
{
	sushi::GameLogic::TimerManager = new sushi::Timer();
	sushi::GameLogic::DisplayManager = new sushi::Display(800, 800, false, false);
	sushi::GameLogic::InputManager = new sushi::Input(DisplayManager);
	sushi::GameLogic::GraphicsManager = new sushi::Graphics();
	sushi::SceneDescription sd = { sushi::SCENE_2D , 1, 0 };
	sushi::GameLogic::GameScene = new sushi::Scene(&sd);
}

void sushi::GameLogic::endGame(void)
{
	delete sushi::GameLogic::GameScene;
	delete sushi::GameLogic::GraphicsManager;
	delete sushi::GameLogic::InputManager;
	delete sushi::GameLogic::DisplayManager;
	delete sushi::GameLogic::TimerManager;
}

void sushi::GameLogic::updateState()
{
	/* Start timer */
	cycleStart = sushi::GameLogic::TimerManager->getTimeMicroSec();
	/* Update the input events */
	sushi::GameLogic::InputManager->pollEvents();
	/* Clear screen */
	sushi::GameLogic::GraphicsManager->clearSGXScreen(161, 230, 151, 255);
}

void sushi::GameLogic::renderState()
{
	sushi::GameLogic::GraphicsManager->renderSGXfixFilledRects();
	sushi::GameLogic::InputManager->swapDisplayBuffer();
	sushi::GameLogic::GraphicsManager->SGXFinishOperation();
	float cycleTime = (float)(sushi::GameLogic::TimerManager->getTimeMicroSec() - cycleStart) / 1000000.0f;
	//std::cout << "Cycle time (s): " << cycleTime << "s" << "\t\t" << "FPS: " << 1.0f / cycleTime << "\t\t" << std::endl;
}

void sushi::GameLogic::addtoScene(Entity* entity)
{
	sushi::GameLogic::GameScene->addNewMember(entity);
}


