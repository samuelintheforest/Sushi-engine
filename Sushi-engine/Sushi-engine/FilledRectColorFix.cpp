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


void sushi::FilledRectColorFix::draw()
{
	//std::cout << "Draw: from FilledRectColorFix class" << std::endl;
}

void sushi::FilledRectColorFix::addElement()
{
	FilledRectColorFixDesc tmpRect;
	this->getDesc(tmpRect);
	sushi::GameLogic::GraphicsManager->addNewfixFilledRect(&tmpRect);

	std::cout << "Added: from FilledRectColorFix class" << std::endl;
}


