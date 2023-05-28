#include "../includes/Display.h"


sushi::Display::Display(u32 screenW, u32 screenH, binary fullscreen, binary vsync)
{
	this->fullscren = fullscreen;
	this->vsync = vsync;
	width = screenW;
	height = screenH;
	window = NULL;
	windowTitle = "Sushi";

	// Meghívom a glfw-t létrehozó függvényt
	initGLFW();
	// Létrehozom az ablakot
	createWindow();

	// Make ontext current
	glfwMakeContextCurrent(window);

}

sushi::Display::~Display(void)
{
	glfwDestroyWindow(window);
	glfwTerminate();
}



void sushi::Display::initGLFW()
{
	glfwInit();

	GLFWerrorfun errorCallbackPtr = (GLFWerrorfun)sushi::Display::errorCallback;
	glfwSetErrorCallback(errorCallbackPtr);

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	// Alap monitor dimenziók lekérése és változók inicializálása
	GLFWmonitor* primary = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(primary);

	monitorWidth = mode->width;
	monitorHeight = mode->height;
	hz = mode->refreshRate;

	//std::cout << monitorWidth << ", " << monitorHeight << std::endl;

	
}

void sushi::Display::createWindow()
{
	if (fullscren)
	{
		GLFWmonitor* primary = glfwGetPrimaryMonitor();
		window = glfwCreateWindow(width, height, windowTitle.c_str(), primary, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			exit(-1);
		}
	}
	else 
	{
		window = glfwCreateWindow(width, height, windowTitle.c_str(), NULL, NULL);
		if (window == NULL)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
			exit(-1);
		}
		
	}
	
}

void sushi::Display::errorCallback(int code, const char* description)
{
	std::cout << "===The ERROR CODE: " << code << "\nSum:  " << description << "\n===" << std::endl;
}

void sushi::Display::enableWindowFullscreen()
{
	if (!this->fullscren)
	{
		GLFWmonitor* primary = glfwGetPrimaryMonitor();
		if (vsync)
		{
			glfwSetWindowMonitor(window, primary, 0, 0, monitorWidth, monitorHeight, hz);
		} else
		{
			glfwSetWindowMonitor(window, primary, 0, 0, monitorWidth, monitorHeight, 0);
		}
		fullscren = true;
	}
}

void sushi::Display::disableWindowFullscreen()
{
	if (this->fullscren)
	{
		if (vsync)
		{
			glfwSetWindowMonitor(window, NULL, 100, 100, width, height, hz);
		}
		else
		{
			glfwSetWindowMonitor(window, NULL, 100, 100, width, height, 0);
		}
		fullscren = false;
	}
}

void sushi::Display::enableWindowVsync()
{
	if (!this->vsync)
	{
		glfwSwapInterval(1);
		this->vsync = true;
	}
}

void sushi::Display::disableWindowVsync()
{
	if (this->vsync)
	{
		glfwSwapInterval(0);
		this->vsync = false;
	}
}

sushi::u32 sushi::Display::getMonitorHz()
{
	return u32(hz);
}

sushi::u32 sushi::Display::getMonitorWidth()
{
	return u32(monitorWidth);
}

sushi::u32 sushi::Display::getMonitorHeight()
{
	return u32(monitorHeight);
}

std::string sushi::Display::getWindowTitle()
{
	return std::string(windowTitle);
}

void sushi::Display::setWindowTitle(const std::string& titleName)
{
	windowTitle = titleName;
	glfwSetWindowTitle(window, windowTitle.c_str());
}

void sushi::Display::setWindowShouldClose(binary value)
{
	if (value)
		glfwSetWindowShouldClose(window, 1);
	else
		glfwSetWindowShouldClose(window, 0);
}

sushi::binary sushi::Display::getWindowShouldClose()
{
	return binary(glfwWindowShouldClose(window));
}


