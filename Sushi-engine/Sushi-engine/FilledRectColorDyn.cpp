#include "GameLogic.h"
#include "FilledRectColorDyn.h"

sushi::FilledRectColorDyn::FilledRectColorDyn() : Rectangle()
{
    this->color = { 0,0,0,0 };
	this->addElement();
}

sushi::FilledRectColorDyn::FilledRectColorDyn(IVec4 args, IVec4 color, int32_t z) : Rectangle(args.x, args.y, z, args.z, args.w)
{
	this->color = color;
	this->addElement();
}

sushi::FilledRectColorDyn::~FilledRectColorDyn()
{

}

void sushi::FilledRectColorDyn::render()
{
    this->addElement();
}

void sushi::FilledRectColorDyn::addElement()
{
    /* 1. Point: LB */
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->pos.x);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)(this->pos.y + this->dim.y));
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.x * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.y * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.z * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.a * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back(-1.0f);

    /* 2. Point: LT */
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->pos.x);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->pos.y);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.x * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.y * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.z * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.a * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back(-1.0f);

    /* 3. Point: LT */
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)(this->pos.x + this->dim.x));
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)(this->pos.y + this->dim.y));
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.x * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.y * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.z * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.a * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back(-1.0f);

    /* 4. Point: LT */
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)(this->pos.x + this->dim.x));
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->pos.y);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->pos.z);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.x * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.y * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.z * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back((float)this->color.a * sushi::colorRatio);
    sushi::GameLogic::GraphicsManager->dynamicFilledRectVertices.push_back(-1.0f);

    sushi::GameLogic::GraphicsManager->setDynRectCount(sushi::GameLogic::GraphicsManager->getDynRectCount() + 1);
	/* std::cout << "Added: from FilledRectColorFix class; FixRectCount: " << sushi::GameLogic::GraphicsManager->fixFilledRectCnt << std::endl; */
}
