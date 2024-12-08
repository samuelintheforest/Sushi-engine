#include "Graphics.h"




sushi::Graphics::Graphics()
{
    this->FilledRectFixShader = nullptr;
    this->FilledRectColorDynShader = nullptr;
    this->FilledRectTexturedDynShader = nullptr;

    this->fixFilledRectVAO = 0;
    this->fixFilledRectVBO = 0;
    this->fixFilledRectEBO = 0;

    this->FilledRectFixModelM4 = Mat4(1.0f);
    this->FilledRectFixViewM4 = Mat4(1.0f);
    this->FilledRectFixProjectionM4 = Mat4(1.0f);
    
    /* Start Graphic operations */

    /* Load Selected graphical function pointers, drivers */
    loadSGXfuncsPtr();
    
    /* Depth, Blending (Transparency), Viewport and Shader settings */
    compileSGXShaders();
    enableSGXDepth();
    enableSGXBlending();
    setSGXViewport(0, 0, 800, 800);
    this->FilledRectFixShader->use();
    this->FilledRectFixProjectionM4 = glm::orthoRH(0.0f, 800.0f, 0.0f, 800.0f, -65535.f, 65535.f);

    setSGXUniformMatrices(this->FilledRectFixModelM4, this->FilledRectFixViewM4, this->FilledRectFixProjectionM4);
    
}

sushi::Graphics::~Graphics()
{
    glDeleteBuffers(1, &this->fixFilledRectVBO);
    glDeleteBuffers(1, &this->fixFilledRectEBO);
    glDeleteVertexArrays(1, &this->fixFilledRectVAO);
    std::cout << "Deleted Graphics" << std::endl;
    delete this->FilledRectFixShader;
}
void sushi::Graphics::loadSGXfuncsPtr()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

void sushi::Graphics::enableSGXBlending()
{
    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void sushi::Graphics::enableSGXDepth()
{
    glEnable(GL_DEPTH_TEST);
}

void sushi::Graphics::disableSGXDepth()
{
    glDisable(GL_DEPTH_TEST);
}
void sushi::Graphics::setSGXViewport(int32_t x, int32_t y, int32_t w, int32_t h)
{
    glViewport(x, y, w, h);
}

void sushi::Graphics::compileSGXShaders()
{
    this->FilledRectFixShader = new SGXShader("shaders\\FilledRectFixShader.vert", "shaders\\FilledRectFixShader.frag", NULL);
    //this->FilledRectColorDynShader = 0;
    //this->FilledRectTexturedDynShader = 0;
}

void sushi::Graphics::setUpSGXVertexMisc()
{
    if (!this->fixFilledRectIndices.size())
    {
        return;
    }
    // Create vertex array of the quad_batch
    glGenVertexArrays(1, &this->fixFilledRectVAO);
    glBindVertexArray(this->fixFilledRectVAO);

    // Create the required vertex buffer object
    glGenBuffers(1, &this->fixFilledRectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->fixFilledRectVBO);
    glBufferData(GL_ARRAY_BUFFER, this->fixFilledRectVertices.size() * sizeof(float), &this->fixFilledRectVertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &this->fixFilledRectEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->fixFilledRectEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->fixFilledRectIndices.size() * sizeof(uint32_t), &this->fixFilledRectIndices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    if (glIsVertexArray(this->fixFilledRectVAO) && glIsBuffer(this->fixFilledRectVBO) && glIsBuffer(this->fixFilledRectEBO))
    {
        std::cout << "DEBUG::ALL BUFFERS/ARRAYS WERE CREATED SUCCESSFULY" << std::endl;
    }
    else
    {
        std::cout << "DEBUG::SOME OF THE BUFFERS/ARRAYS WEREN\'T CREATED" << std::endl;
    }


    /* Binding textures to shaders */
    for (auto& val : this->textureSlot)
    {
        std::stringstream sbuff;
        sbuff << "txs_" << val;
        this->FilledRectFixShader->use();
        this->FilledRectFixShader->setInt(sbuff.str(), val);
    }
    
}

void sushi::Graphics::setSGXUniformMatrices(const Mat4& model, const Mat4& view, const Mat4& proj)
{
    this->FilledRectFixShader->use();
    this->FilledRectFixShader->setMat4("model", model);
    this->FilledRectFixShader->setMat4("camera", view);
    this->FilledRectFixShader->setMat4("projection", proj);
}

void sushi::Graphics::renderSGXfixFilledRects()
{
    if (!this->fixFilledRectIndices.size())
    {
        return;
    }

    setSGXUniformMatrices(this->FilledRectFixModelM4, this->FilledRectFixViewM4, this->FilledRectFixProjectionM4);
    for (auto& val : this->textureSlot)
    {
        glActiveTexture(GL_TEXTURE0 + val);
        glBindTexture(GL_TEXTURE_2D, val);
    }
    
    glBindVertexArray(this->fixFilledRectVAO);
    glDrawElements(GL_TRIANGLES, (int)this->fixFilledRectIndices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
    
}

void sushi::Graphics::clearSGXScreen(uint8_t r, uint8_t g, uint8_t b, uint8_t w)
{
    glClearColor(sushi::colorRatio * r, sushi::colorRatio * g, sushi::colorRatio * b, sushi::colorRatio * w);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void sushi::Graphics::SGXFinishOperation()
{
    glFinish();
}
