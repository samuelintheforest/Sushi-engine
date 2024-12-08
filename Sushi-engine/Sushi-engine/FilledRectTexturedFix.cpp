#include "FilledRectTexturedFix.h"
#include "GameLogic.h"

sushi::FilledRectTexturedFix::FilledRectTexturedFix(IVec4 args, int32_t z, Vec4 txInfo, const SGXTexture* tx) : Rectangle(args.x, args.y, z, args.z, args.w)
{
    this->txAttrib = { txInfo.x, txInfo.y, txInfo.z, txInfo.w};
    //this->txAttrib = { 0.0f, 0.0f, 1.0f, 1.0f };
    this->txID = tx->getTextureID();
    this->txW = tx->getTextureWidth();
    this->txH = tx->getTextureHeight();

    this->addElement();

}

sushi::FilledRectTexturedFix::~FilledRectTexturedFix()
{
    /* Object is destroyed */
}

void sushi::FilledRectTexturedFix::addElement()
{
    uint32_t indices_offset = (uint32_t)sushi::GameLogic::GraphicsManager->fixFilledRectVertices.size() / 8; /* 8 float vertex data */

    /* 1. Point: LB */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.x);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.y + this->dim.y));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(this->txAttrib.x);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(this->txAttrib.y);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f); 
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->txID);

    /* 2. Point: LT */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.x);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.y);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(this->txAttrib.x);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(this->txAttrib.y + this->txAttrib.w);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->txID);

    /* 3. Point: RB */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.x + this->dim.x));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.y + this->dim.y));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(this->txAttrib.x + this->txAttrib.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(this->txAttrib.y);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->txID);

    /* 4. Point: RT */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.x + this->dim.x));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.y);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(this->txAttrib.x + this->txAttrib.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(this->txAttrib.y + this->txAttrib.w);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->txID);

    /* Adding the indices to FixIndices */
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(0 + indices_offset);
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(1 + indices_offset);
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(2 + indices_offset);
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(1 + indices_offset);
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(2 + indices_offset);
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(3 + indices_offset);

    //std::cout << "Added: from FilledRectTexturedFix class; FixRectCount: " << sushi::GameLogic::GraphicsManager->fixFilledRectCnt << std::endl;
}
