#include "Graphics.h"




sushi::Graphics::Graphics(uint32_t maxDynRect)
{
    this->FilledRectFixShader = nullptr;
    this->FilledRectColorDynShader = nullptr;
    this->FilledRectTexturedDynShader = nullptr;

    this->fixFilledRectVAO = 0;
    this->fixFilledRectVBO = 0;
    this->fixFilledRectEBO = 0;

    this->dynFilledRectVAO = 0;
    this->dynFilledRectVBO = 0;
    this->dynFilledRectEBO = 0;

    this->FilledRectFixModelM4 = Mat4(1.0f);
    this->FilledRectFixViewM4 = Mat4(1.0f);
    this->FilledRectFixProjectionM4 = Mat4(1.0f);
    
    this->maxDynRect = maxDynRect;
    this->dynRectCount = 0;
    /* Start Graphic operations */

    /* Load Selected graphical function pointers, drivers */
    loadSGXfuncsPtr();
    
    /* Depth, Blending (Transparency), Viewport and Shader settings */
    compileSGXShaders();
    //enableSGXDepth();
    enableSGXBlending();
    setSGXViewport(0, 0, 800, 800);
    this->FilledRectFixShader->use();
    this->FilledRectFixProjectionM4 = glm::orthoRH(0.0f, 800.0f, 0.0f, 800.0f, -65535.f, 65535.f);
    
    setSGXUniformMatrices(this->FilledRectFixModelM4, this->FilledRectFixViewM4, this->FilledRectFixProjectionM4);

    /* Generate premade Indices (dynamic rectangle) */
    this->initDynFilledRectIndicesBuffer();
    this->setUpSGXDynVertexMisc();
    
}

sushi::Graphics::~Graphics()
{
    glDeleteBuffers(1, &this->fixFilledRectVBO);
    glDeleteBuffers(1, &this->fixFilledRectEBO);
    glDeleteVertexArrays(1, &this->fixFilledRectVAO);

    glDeleteBuffers(1, &this->dynFilledRectVBO);
    glDeleteBuffers(1, &this->dynFilledRectEBO);
    glDeleteVertexArrays(1, &this->dynFilledRectVAO);

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
    glDepthFunc(GL_LESS);
    glDepthMask(GL_TRUE);
}

void sushi::Graphics::disableSGXDepth()
{
    glDisable(GL_DEPTH_TEST);
}
void sushi::Graphics::setSGXViewport(int32_t x, int32_t y, int32_t w, int32_t h)
{
    glViewport(x, y, w, h);
}

void sushi::Graphics::setDynRectCount(uint32_t number)
{
    this->dynRectCount = number;
}



uint32_t sushi::Graphics::getDynRectCount()
{
    return this->dynRectCount;
}

void sushi::Graphics::setSGXViewMatrix(const Mat4 &view)
{
    this->FilledRectFixViewM4 = view;
}

sushi::Mat4& sushi::Graphics::getSGXViewMatrix()
{
    return this->FilledRectFixViewM4;
}

void sushi::Graphics::setSGXModelMatrix(const Mat4 &model)
{
    this->FilledRectFixModelM4 = model;
}

sushi::Mat4 &sushi::Graphics::getSGXModelMatrix()
{
    return this->FilledRectFixModelM4;
}

void sushi::Graphics::setSGXProjectionMatrix(const Mat4 &proj)
{
    this->FilledRectFixProjectionM4 = proj;
}

sushi::Mat4 &sushi::Graphics::getSGXProjectionMatrix()
{
    return this->FilledRectFixProjectionM4;
}

void sushi::Graphics::compileSGXShaders()
{
    this->FilledRectFixShader = new SGXShader("shaders/FilledRectFixShader.vert", "shaders/FilledRectFixShader.frag", NULL);
    //this->FilledRectColorDynShader = 0;
    //this->FilledRectTexturedDynShader = 0;
}

void sushi::Graphics::initDynFilledRectIndicesBuffer()
{

    uint32_t indices_offset = 0; /* 8 float vertex data */

    for (uint32_t i = 0; i < this->maxDynRect; i++)
    {
            this->dynamicFilledRectIndices.push_back(0 + indices_offset);
            this->dynamicFilledRectIndices.push_back(1 + indices_offset);
            this->dynamicFilledRectIndices.push_back(2 + indices_offset);
            this->dynamicFilledRectIndices.push_back(1 + indices_offset);
            this->dynamicFilledRectIndices.push_back(2 + indices_offset);
            this->dynamicFilledRectIndices.push_back(3 + indices_offset);

            indices_offset += 4;
    }
}

void sushi::Graphics::bindTextures()
{
    for (auto& val : this->textureSlot)
    {
        std::stringstream sbuff;
        sbuff << "txs_" << val;
        this->FilledRectFixShader->use();
        this->FilledRectFixShader->setInt(sbuff.str(), val);
    }
}

void sushi::Graphics::configureFixOpaqueColourRectsSGX()
{
    
}

void sushi::Graphics::configureFixTransparentColourRectsSGX()
{

}

void sushi::Graphics::configureFixTransparentTextureRectsSGX()
{

}

void sushi::Graphics::configureDynOpaqueColourRectsSGX()
{

}

void sushi::Graphics::configureDynTransparentColourRectsSGX()
{
    
}

void sushi::Graphics::configureDynTransparentTextureRectsSGX()
{
    
}

void sushi::Graphics::updateDynVBO()
{
    glBindVertexArray(this->dynFilledRectVAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->dynFilledRectVBO);
    glBufferData(GL_ARRAY_BUFFER, this->maxDynRect * 32 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, this->dynamicFilledRectVertices.size() * sizeof(float), &this->dynamicFilledRectVertices[0]);
    glBindVertexArray(0);
}

void sushi::Graphics::resetDynRectBuffer()
{
    this->dynamicFilledRectVertices.clear();
    this->dynRectCount = 0;
}

void sushi::Graphics::setUpSGXFixVertexMisc()
{
    // if (!this->fixFilledRectIndices.size())
    // {
    //     return;
    // }
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
    this->bindTextures();
    
}

void sushi::Graphics::setUpSGXDynVertexMisc()
{
    // Create vertex array of the quad_batch
    glGenVertexArrays(1, &this->dynFilledRectVAO);
    glBindVertexArray(this->dynFilledRectVAO);

    // Create the required vertex buffer object
    glGenBuffers(1, &this->dynFilledRectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->dynFilledRectVBO);
    glBufferData(GL_ARRAY_BUFFER, this->maxDynRect * 32 * sizeof(float), nullptr, GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(7 * sizeof(float)));
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &this->dynFilledRectEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->dynFilledRectEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->dynamicFilledRectIndices.size() * sizeof(uint32_t), &this->dynamicFilledRectIndices[0], GL_STATIC_DRAW);

    glBindVertexArray(0);

    if (glIsVertexArray(this->dynFilledRectVAO) && glIsBuffer(this->dynFilledRectVBO) && glIsBuffer(this->dynFilledRectEBO))
    {
        std::cout << "DEBUG::ALL BUFFERS/ARRAYS WERE CREATED SUCCESSFULY" << std::endl;
    }
    else
    {
        std::cout << "DEBUG::SOME OF THE BUFFERS/ARRAYS WEREN\'T CREATED" << std::endl;
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
    updateDynVBO();

    /* Rendering fix rects */
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
    glBindVertexArray(this->dynFilledRectVAO);
    glDrawElements(GL_TRIANGLES, (int)this->dynRectCount * 6, GL_UNSIGNED_INT, 0);
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
