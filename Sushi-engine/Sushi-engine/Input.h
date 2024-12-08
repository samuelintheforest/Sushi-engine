#ifndef INPUT_H
#define INPUT_H


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
		Input();
		~Input();
		void pollEvents();
		void swapDisplayBuffer();

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
		static uint32_t joystickPresent[16];
		GLFWwindow* WindowPtr;
		
	};
}

#endif // !INPUT_H




