#include "FilledRectTexturedFix.h"
#include "GameLogic.h"

sushi::FilledRectTexturedFix::FilledRectTexturedFix(IVec4 args, int32_t z, Vec4 txInfo, const Texture* tx) : Rectangle(args.x, args.y, z, args.z, args.w)
{
    this->txAttrib = { txInfo.x, txInfo.y, txInfo.z, txInfo.w};
    this->txAttrib = { 0.0f, 0.0f, 1.0f, 1.0f };
    this->txID = tx->txId;
    this->txW = tx->width;
    this->txH = tx->height;

    this->addElement();

}

sushi::FilledRectTexturedFix::~FilledRectTexturedFix()
{
    /* Object is destroyed */
}

void sushi::FilledRectTexturedFix::addElement()
{
    /* 1. Point: LB */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.x);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.y + this->dim.y));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f); 
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->txID);

    /* 2. Point: LT */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.x);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.y);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(1.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->txID);

    /* 3. Point: RB */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.x + this->dim.x));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.y + this->dim.y));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(1.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->txID);

    /* 4. Point: RT */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.x + this->dim.x));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.y);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(1.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(1.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->txID);

    sushi::GameLogic::GraphicsManager->fixFilledRectVerticesCnt += 32; /* 8 * 4 = 32 */

    /* Adding the indices to FixIndices */
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(0 + sushi::GameLogic::GraphicsManager->fixFilledRectIndicesOffset);
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(1 + sushi::GameLogic::GraphicsManager->fixFilledRectIndicesOffset);
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(2 + sushi::GameLogic::GraphicsManager->fixFilledRectIndicesOffset);
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(1 + sushi::GameLogic::GraphicsManager->fixFilledRectIndicesOffset);
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(2 + sushi::GameLogic::GraphicsManager->fixFilledRectIndicesOffset);
    sushi::GameLogic::GraphicsManager->fixFilledRectIndices.push_back(3 + sushi::GameLogic::GraphicsManager->fixFilledRectIndicesOffset);

    sushi::GameLogic::GraphicsManager->fixFilledRectIndicesCnt += 6;
    sushi::GameLogic::GraphicsManager->fixFilledRectIndicesOffset += 4;

    sushi::GameLogic::GraphicsManager->fixFilledRectCnt++;

    std::cout << "Added: from FilledRectTexturedFix class; FixRectCount: " << sushi::GameLogic::GraphicsManager->fixFilledRectCnt << std::endl;
}
