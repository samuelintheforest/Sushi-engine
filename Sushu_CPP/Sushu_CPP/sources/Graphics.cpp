#include "../includes/Graphics.h"


sushi::Graphics::Graphics()
{
    loadSGXfuncsPtr();
}

sushi::Graphics::~Graphics()
{

}

inline void sushi::Graphics::enableSGXDepth()
{
    glEnable(GL_DEPTH);
}

inline void sushi::Graphics::disableSGXDepth()
{
    glDisable(GL_DEPTH);
}

inline void sushi::Graphics::setSGXViewport(int32_t x, int32_t y, int32_t w, int32_t h)
{
    glViewport(x, y, w, h);
}

void sushi::Graphics::loadSGXfuncsPtr()
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
