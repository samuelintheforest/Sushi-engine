#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <iostream>
#include <vector>
#include "Display.h"
#include "Graphics.h"
#include "Input.h"
#include "Scene.h"
#include "Timer.h"

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
		static void initGame(void);
		static void endGame(void);

		static Display *DisplayManager;
		static Input *InputManager;
		static Graphics* GraphicsManager;
		static std::vector<Scene> GameScenes;
		static Timer* TimerManager;
	};
}


#endif // !GAME_LOGIC_H

