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
    

	// glad: bet�ltjuk az �sszes f�ggv�ny pointert a f�jlba
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}
