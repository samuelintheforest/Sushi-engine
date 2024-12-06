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
	GameLogic osztály: kezeli a játék alaplogikáját. Innen érhetõ el minden alfunkció:
		- Display osztály (kezeli az ablakot az operációs rendszeren ( ezt a glfw könytárral teszi) + monitor setup)
		- Scene osztályok (ezt egy std::vector típusban tárolva) a játék alap jelenetei
		- Input osztály - ez kezeli az alapvetõ inputokat, mint: billentyûzet, egér, kontrollerek
		- Graphics osztály - ebben van benne a grafikai backend menedzselése

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

