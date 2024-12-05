#include "../includes/Graphics.h"


sushi::Graphics::Graphics()
{
    this->FilledRectColorFixShader = nullptr;
    this->FilledRectColorDynShader = nullptr;
    this->FilledRectTexturedFixShader = nullptr;
    this->FilledRectTexturedDynShader = nullptr;

    loadSGXfuncsPtr();
    compileSGXShaders();
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
	// glad: loads the OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        exit(-1);
    }
}

void sushi::Graphics::compileSGXShaders()
{
    this->FilledRectColorFixShader = new Shader("shaders\\FilledRectColorFixShader.vs", "shaders\\FilledRectColorFixShader.fs", nullptr);
    //this->FilledRectColorDynShader = 0;
    //this->FilledRectTexturedFixShader = 0;
    //this->FilledRectTexturedDynShader = 0;
}
