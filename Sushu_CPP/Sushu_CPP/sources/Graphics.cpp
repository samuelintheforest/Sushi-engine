#include "../includes/Graphics.h"


sushi::Graphics::Graphics()
{
    loadGraphicfuncsPtr();
}

sushi::Graphics::~Graphics()
{

}

void sushi::Graphics::loadGraphicfuncsPtr()
{
    // Make opengl context
    

	// glad: betöltjuk az összes függvény pointert a fájlba
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}
