#ifndef INPUT_H
#define INPUT_H

#include "EssentialInlcudes.h"
#include <GLFW/glfw3.h>
#include "Display.h"

namespace sushi
{
	/*
	Input osztály:
	- Bemenetek kezelése: Egér, Billentyûzet, Kontrollerek
	- Eventek definiálása
	*/
	class Input
	{
	public:
		// Konstruktor és Destruktor definiálása
		Input(Display* displayPtr);
		~Input();
		void pollEvents();

		static s32 joystickPresent[16];
		
	private:
		// Keyboard events callback
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		// Mouse position callback
		static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		// Mouse button callback
		static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		// Mouse scroll event
		static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
		// Mouse enter/leave context callback
		static void cursor_enter_callback(GLFWwindow* window, int entered);
		// Joystick connected/disconnected
		static void joystick_callback(int jid, int event);
		// Joystick jelen van-e vagy sem
		static void check_joysticks_present();

		
		static GLFWwindow* WindowPtr;
		static Display* DisplayPtr;
		
	};
}

#endif // !INPUT_H




