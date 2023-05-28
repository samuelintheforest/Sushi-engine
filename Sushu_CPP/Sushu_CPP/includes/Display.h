#ifndef DISPLAY_H
#define DISPLAY_H

#include "EssentialInlcudes.h"
#include <GLFW/glfw3.h>

namespace sushi
{
	class Display
	{
	public:
		// === Publikus f�ggv�nyek ===
		// A Display oszt�ly konstruktora / destruktora
		Display(u32 screenW, u32 screenH, binary fullscreen = false, binary vsync = true);
		~Display(void);

		// Ablak �llapot v�ltoz�sok
		void enableWindowFullscreen();
		void disableWindowFullscreen();
		void enableWindowVsync();
		void disableWindowVsync();

		// Getterek �s szetterek helyi v�ltoz�khoz
		u32 getMonitorHz();
		u32 getMonitorWidth();
		u32 getMonitorHeight();
		std::string getWindowTitle();
		void setWindowTitle(const std::string &titleName);
		void setWindowShouldClose(binary value);
		binary getWindowShouldClose();


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
