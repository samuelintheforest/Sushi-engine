#include "../includes/Graphics.h"


sushi::Graphics::Graphics()
{
    loadGraphicalLib();
}

sushi::Graphics::~Graphics()
{

}

void sushi::Graphics::loadGraphicalLib()
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
