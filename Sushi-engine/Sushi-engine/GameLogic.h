#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H


#include "Display.h"
#include "Graphics.h"
#include "Input.h"
#include "Scene.h"
#include "Timer.h"
#include "TimerThread.h"
#include "Entity.h"
#include "Types.h"

#include <iostream>
#include <vector>




namespace sushi 
{

	/*
	GameLogic oszt�ly: kezeli a j�t�k alaplogik�j�t. Innen �rhet� el minden alfunkci�:
		- Display oszt�ly (kezeli az ablakot az oper�ci�s rendszeren ( ezt a glfw k�nyt�rral teszi) + monitor setup)
		- Scene oszt�lyok (ezt egy std::vector t�pusban t�rolva) a j�t�k alap jelenetei
		- Input oszt�ly - ez kezeli az alapvet� inputokat, mint: billenty�zet, eg�r, kontrollerek
		- Graphics oszt�ly - ebben van benne a grafikai backend menedzsel�se

	*/
	class GameLogic
	{
	public:
		static void initGame();
		static void endGame();
		static void updateState();
		static void renderState();
		static void addtoScene(Entity* entity);

		static Display *DisplayManager;
		static Input *InputManager;
		static Graphics* GraphicsManager;
		static Scene* GameScene;
		static Timer* TimerManager;
		
	};
}


#endif // !GAME_LOGIC_H

