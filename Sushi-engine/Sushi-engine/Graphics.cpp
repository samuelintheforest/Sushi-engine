#include "Graphics.h"




sushi::Graphics::Graphics()
{
    this->FilledRectColorFixShader = nullptr;
    this->FilledRectColorDynShader = nullptr;
    this->FilledRectTexturedFixShader = nullptr;
    this->FilledRectTexturedDynShader = nullptr;

    this->fixFilledRectVerticesCnt = 0;
    this->fixFilledRectIndicesCnt = 0;
    this->fixFilledRectIndicesOffset = 0;
    this->fixFilledRectCnt = 0;

    this->fixFilledRectVAO = 0;
    this->fixFilledRectVBO = 0;
    this->fixFilledRectEBO = 0;

    FilledRectColorFixModelM4 = Mat4(1);
    FilledRectColorFixViewM4 = Mat4(1);
    FilledRectColorFixProjectionM4 = Mat4(1);

    /* Start Graphic operations */

    /* Load Selected graphical function pointers, drivers */
    loadSGXfuncsPtr();
    
    /* Depth, Viewport and Shader settings */
    enableSGXDepth();
    setSGXViewport(0, 0, 800, 800);
    compileSGXShaders();

    FilledRectColorFixShader->use();
    FilledRectColorFixProjectionM4 = glm::orthoRH(0.0f, 800.0f, 0.0f, 800.0f, -65535.f, 65535.f);
    setSGXUniformMatrices(FilledRectColorFixModelM4, FilledRectColorFixViewM4, FilledRectColorFixProjectionM4);
    
}

sushi::Graphics::~Graphics()
{
    glDeleteBuffers(1, &fixFilledRectVBO);
    glDeleteBuffers(1, &fixFilledRectEBO);
    glDeleteVertexArrays(1, &fixFilledRectVAO);
    std::cout << "Deleted Graphics" << std::endl;
    delete FilledRectColorFixShader;
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

void sushi::Graphics::addNewfixFilledRect(FilledRectColorFixDesc* rect)
{
    /* Adding FilledRectColorFix Vertices to Fix Vertices */

    

/* 1. Point: LB */
    this->fixFilledRectVertices.push_back((float)rect->x);
    this->fixFilledRectVertices.push_back((float)(rect->y + rect->h));
    this->fixFilledRectVertices.push_back((float)rect->z);
    this->fixFilledRectVertices.push_back((float)rect->r * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->g * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->b * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->a * sushi::colorRatio);

    /* 2. Point: LT */
    this->fixFilledRectVertices.push_back((float)rect->x);
    this->fixFilledRectVertices.push_back((float)rect->y);
    this->fixFilledRectVertices.push_back((float)rect->z);
    this->fixFilledRectVertices.push_back((float)rect->r * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->g * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->b * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->a * sushi::colorRatio);

    /* 3. Point: LT */
    this->fixFilledRectVertices.push_back((float)(rect->x + rect->w));
    this->fixFilledRectVertices.push_back((float)(rect->y + rect->h));
    this->fixFilledRectVertices.push_back((float)rect->z);
    this->fixFilledRectVertices.push_back((float)rect->r * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->g * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->b * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->a * sushi::colorRatio);

    /* 4. Point: LT */
    this->fixFilledRectVertices.push_back((float)(rect->x + rect->w));
    this->fixFilledRectVertices.push_back((float)rect->y);
    this->fixFilledRectVertices.push_back((float)rect->z);
    this->fixFilledRectVertices.push_back((float)rect->r * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->g * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->b * sushi::colorRatio);
    this->fixFilledRectVertices.push_back((float)rect->a * sushi::colorRatio);

    this->fixFilledRectVerticesCnt += 28; /* 7 * 4 = 28 */
    
    /* Adding the indices to FixIndices */
    this->fixFilledRectIndices.push_back(0 + this->fixFilledRectIndicesOffset);
    this->fixFilledRectIndices.push_back(1 + this->fixFilledRectIndicesOffset);
    this->fixFilledRectIndices.push_back(2 + this->fixFilledRectIndicesOffset);
    this->fixFilledRectIndices.push_back(1 + this->fixFilledRectIndicesOffset);
    this->fixFilledRectIndices.push_back(2 + this->fixFilledRectIndicesOffset);
    this->fixFilledRectIndices.push_back(3 + this->fixFilledRectIndicesOffset);

    this->fixFilledRectIndicesCnt += 6;
    this->fixFilledRectIndicesOffset += 4;

    this->fixFilledRectCnt++;


}

void sushi::Graphics::loadSGXfuncsPtr()
{
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

void sushi::Graphics::compileSGXShaders()
{
    this->FilledRectColorFixShader = new GLShader("shaders\\FilledRectColorFixShader.vert", "shaders\\FilledRectColorFixShader.frag", NULL);
    //this->FilledRectColorDynShader = 0;
    //this->FilledRectTexturedFixShader = 0;
    //this->FilledRectTexturedDynShader = 0;
}

void sushi::Graphics::setUpSGXVertexMisc()
{
    // Create vertex array of the quad_batch
    glGenVertexArrays(1, &fixFilledRectVAO);
    glBindVertexArray(fixFilledRectVAO);

    // Create the required vertex buffer object
    glGenBuffers(1, &fixFilledRectVBO);
    glBindBuffer(GL_ARRAY_BUFFER, fixFilledRectVBO);
    glBufferData(GL_ARRAY_BUFFER, fixFilledRectVertices.size() * sizeof(GLfloat), &fixFilledRectVertices[0], GL_STATIC_DRAW);
    //GLbitfield flagsForBuffer = GL_DYNAMIC_STORAGE_BIT | GL_MAP_WRITE_BIT | GL_MAP_PERSISTENT_BIT | GL_MAP_COHERENT_BIT;
    //glBufferStorage(GL_ARRAY_BUFFER, 4 * 9 * sizeof(float) * maxBatch, NULL, flagsForBuffer);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glGenBuffers(1, &fixFilledRectEBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, fixFilledRectEBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, fixFilledRectIndices.size() * sizeof(GLuint), &fixFilledRectIndices[0], GL_STATIC_DRAW);

    /*
    TODO: Font atlas texture unit set in shader
    TODO: setting the normal texture ids in the shader
    */

    /*glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);*/
    glBindVertexArray(0);

    if (glIsVertexArray(fixFilledRectVAO) && glIsBuffer(fixFilledRectVBO) && glIsBuffer(fixFilledRectEBO))
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
    this->FilledRectColorFixShader->use();
    this->FilledRectColorFixShader->setMat4("model", model);
    this->FilledRectColorFixShader->setMat4("camera", view);
    this->FilledRectColorFixShader->setMat4("projection", proj);
}

void sushi::Graphics::renderSGXfixFilledRects()
{
    this->FilledRectColorFixShader->use();
    glBindVertexArray(fixFilledRectVAO);
    glDrawElements(GL_TRIANGLES, fixFilledRectIndicesCnt, GL_UNSIGNED_INT, 0);
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
