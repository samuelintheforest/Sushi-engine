#ifndef DISPLAY_H
#define DISPLAY_H

#include "EssentialInlcudes.h"
#include <GLFW/glfw3.h>

namespace sushi
{
	class Display
	{
	public:
		// === Publikus függvények ===
		// A Display osztály konstruktora / destruktora
		Display(u32 screenW, u32 screenH, binary fullscreen = false, binary vsync = true);
		~Display(void);

		// Ablak állapot változások
		void enableWindowFullscreen();
		void disableWindowFullscreen();
		void enableWindowVsync();
		void disableWindowVsync();

		// Getterek és szetterek helyi változókhoz
		u32 getMonitorHz();
		u32 getMonitorWidth();
		u32 getMonitorHeight();
		std::string getWindowTitle();
		void setWindowTitle(const std::string &titleName);
		void setWindowShouldClose(binary value);
		binary getWindowShouldClose();


		// === Member változók - publikus osztélyváltozók ===
		GLFWwindow* window;

	private:
		// A glfw könyvtár aktiválodík
		void initGLFW();
		// A glfw window létrehozó függvény
		void createWindow();
		// Hibákhoz - függvényhívás (callback)
		static void errorCallback(int code, const char* description);
		

		// Field változók - helyi változók
		binary fullscren;
		binary vsync;
		u32 width;
		u32 height;
		u32 monitorWidth;
		u32 monitorHeight;
		u32 hz;
		std::string windowTitle;
	};
}

#endif // !DISPLAY_H
