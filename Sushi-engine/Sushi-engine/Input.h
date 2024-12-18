#ifndef INPUT_H
#define INPUT_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Display.h"


namespace sushi
{
	/*
	Input oszt�ly:
	- Bemenetek kezel�se: Eg�r, Billenty�zet, Kontrollerek
	- Eventek defini�l�sa
	*/
	class Input
	{
	public:
		// Konstruktor �s Destruktor defini�l�sa
		Input(Display* displayPtr);
		~Input();
		void pollEvents();
		void swapDisplayBuffer();

		static uint32_t joystickPresent[16];
		
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




