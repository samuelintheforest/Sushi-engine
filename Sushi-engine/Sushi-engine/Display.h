#ifndef DISPLAY_H
#define DISPLAY_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

namespace sushi
{
	class Display
	{
	public:
		// === Publikus f�ggv�nyek ===
		// A Display oszt�ly konstruktora / destruktora
		Display(uint32_t screenW, uint32_t screenH, bool fullscreen = false, bool vsync = true);
		~Display();

		// Ablak �llapot v�ltoz�sok
		void enableWindowFullscreen();
		void disableWindowFullscreen();
		void enableWindowVsync();
		void disableWindowVsync();

		// Getterek �s szetterek helyi v�ltoz�khoz
		uint32_t getMonitorHz();
		uint32_t getMonitorWidth();
		uint32_t getMonitorHeight();
		std::string getWindowTitle();
		void setWindowTitle(const std::string &titleName);
		void setWindowShouldClose(bool value);
		bool getWindowShouldClose();


		// === Member v�ltoz�k - publikus oszt�lyv�ltoz�k ===
		GLFWwindow* window;


	private:
		// A glfw k�nyvt�r aktiv�lod�k
		void initGLFW();
		// A glfw window l�trehoz� f�ggv�ny
		void createWindow();
		// Hib�khoz - f�ggv�nyh�v�s (callback)
		static void errorCallback(int code, const char* description);
		

		// Field v�ltoz�k - helyi v�ltoz�k
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
