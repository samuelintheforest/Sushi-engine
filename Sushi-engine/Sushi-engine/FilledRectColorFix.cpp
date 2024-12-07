#include "GameLogic.h"
#include "FilledRectColorFix.h"


sushi::FilledRectColorFix::FilledRectColorFix() : Rectangle()
{
	this->color = { 0,0,0,0 };
	this->addElement();
}

sushi::FilledRectColorFix::FilledRectColorFix(IVec4 args, IVec4 color, int32_t z) : Rectangle(args.x, args.y, z, args.z, args.w)
{
	this->color = color;
	this->addElement();
}

sushi::FilledRectColorFix::~FilledRectColorFix()
{

}

void sushi::FilledRectColorFix::getDesc(FilledRectColorFixDesc& rectDesc)
{
	rectDesc = {
		this->pos.x,
		this->pos.y,
		this->pos.z,
		this->dim.x,
		this->dim.y,
		this->color.x,
		this->color.y,
		this->color.z,
		this->color.w
	};
}


void sushi::FilledRectColorFix::addElement()
{
    /* 1. Point: LB */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.x);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.y + this->dim.y));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.x * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.y * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.z * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.a * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);

    /* 2. Point: LT */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.x);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.y);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.x * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.y * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.z * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.a * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);

    /* 3. Point: LT */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.x + this->dim.x));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.y + this->dim.y));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.x * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.y * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.z * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.a * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);

    /* 4. Point: LT */
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)(this->pos.x + this->dim.x));
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.y);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.x * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.y * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.z * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back((float)this->color.a * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->fixFilledRectVertices.push_back(0.0f);

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

	std::cout << "Added: from FilledRectColorFix class; FixRectCount: " << sushi::GameLogic::GraphicsManager->fixFilledRectCnt << std::endl;
}


