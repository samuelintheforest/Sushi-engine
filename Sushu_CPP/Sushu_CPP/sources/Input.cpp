#include "../includes/Input.h"

GLFWwindow* sushi::Input::WindowPtr = NULL;
sushi::Display* sushi::Input::DisplayPtr = NULL;
// Init Joystick avaliability
uint32_t sushi::Input::joystickPresent[16];


sushi::Input::Input(Display* displayPtr)
{
	DisplayPtr = displayPtr;
	WindowPtr = displayPtr->window;

	// A callback függvények beállítása
	glfwSetKeyCallback(WindowPtr, (GLFWkeyfun)key_callback);
	glfwSetCursorPosCallback(WindowPtr, (GLFWcursorposfun)cursor_position_callback);
	glfwSetCursorEnterCallback(WindowPtr, (GLFWcursorenterfun)cursor_enter_callback);
	glfwSetMouseButtonCallback(WindowPtr, (GLFWmousebuttonfun)mouse_button_callback);
	glfwSetScrollCallback(WindowPtr, (GLFWscrollfun)scroll_callback);
	glfwSetJoystickCallback((GLFWjoystickfun)joystick_callback);

	for (int i = 0; i < sizeof(joystickPresent) / sizeof(uint32_t); i++)
	{
		joystickPresent[i] = 0;
	}
	check_joysticks_present();
	
}

sushi::Input::~Input()
{
}

void sushi::Input::pollEvents()
{
	glfwPollEvents();
}

void sushi::Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	window;
	std::cout << "=== EVENT: (Keyboard) |||  Key: " << key << ", Scancode: " << scancode << ", Action: " << action << ", Mods: " << mods << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		DisplayPtr->setWindowShouldClose(true);
	}
}

void sushi::Input::cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
	window;
	std::cout << "=== EVENT: (Mouse) ||| Xpos: " << xpos << ", Ypos: " << ypos << std::endl;
}

void sushi::Input::mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
	window;
	std::cout << "=== EVENT: (Mouse) ||| Button: " << button << ", Action: " << action << ", Mods: " << mods << std::endl;
}

void sushi::Input::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	window;
	std::cout << "=== EVENT: (Mouse) ||| Scroll: xoffset: " << xoffset << ", yoffset: " << yoffset << std::endl;
}

void sushi::Input::cursor_enter_callback(GLFWwindow* window, int entered)
{
	window;
	std::cout << "=== EVENT: (Mouse) ||| Entered: " << entered << std::endl;
}

void sushi::Input::joystick_callback(int jid, int event)
{
	std::cout << "=== EVENT: (Joystick) ||| Joystick id: " << jid << ", event: " << event << std::endl;
	check_joysticks_present();
}

void sushi::Input::check_joysticks_present()
{
	for (int i = 0; i < sizeof(joystickPresent) / sizeof(uint32_t); i++)
	{
		joystickPresent[i] = glfwJoystickPresent(i);
		const char* name = glfwGetJoystickName(i);
		name;
		std::cout << "=== EVENT: (Joystick) ||| Jid: GLFW_JOYSTICK_" << i + 1 << ", present: " << joystickPresent[i] << std::endl;
	}
}

