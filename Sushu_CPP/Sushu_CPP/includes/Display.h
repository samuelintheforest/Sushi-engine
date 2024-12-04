#ifndef DISPLAY_H
#define DISPLAY_H

#include "../../../vendor/include/glad/glad.h"
#include "../../../vendor/include/GLFW/glfw3.h"

#include <iostream>

namespace sushi
{
	class Display
	{
	public:
		// === Publikus függvények ===
		// A Display osztály konstruktora / destruktora
		Display(uint32_t screenW, uint32_t screenH, bool fullscreen = false, bool vsync = true);
		~Display(void);

		// Ablak állapot változások
		void enableWindowFullscreen();
		void disableWindowFullscreen();
		void enableWindowVsync();
		void disableWindowVsync();

		// Getterek és szetterek helyi változókhoz
		uint32_t getMonitorHz();
		uint32_t getMonitorWidth();
		uint32_t getMonitorHeight();
		std::string getWindowTitle();
		void setWindowTitle(const std::string &titleName);
		void setWindowShouldClose(bool value);
		bool getWindowShouldClose();


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
		bool fullscren;
		bool vsync;
		uint32_t width;
		uint32_t height;
		uint32_t monitorWidth;
		uint32_t monitorHeight;
		uint32_t hz;
		std::string windowTitle;
	};
}

#endif // !DISPLAY_H
