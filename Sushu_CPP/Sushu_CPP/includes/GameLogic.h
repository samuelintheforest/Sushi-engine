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
	GameLogic osztály: kezeli a játék alaplogikáját. Innen érhetõ el minden alfunkció:
		- Display osztály (kezeli az ablakot az operációs rendszeren ( ezt a glfw könytárral teszi) + monitor setup)
		- Scene osztályok (ezt egy std::vector típusban tárolva) a játék alap jelenetei
		- Input osztály - ez kezeli az alapvetõ inputokat, mint: billentyûzet, egér, kontrollerek
		- Graphics osztály - ebben van benne a grafikai backend menedzselése

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

