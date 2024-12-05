#include "../includes/FilledRectColorFix.h"

sushi::FilledRectColorFix::FilledRectColorFix() : Rectangle()
{
	this->color = { 0,0,0,0 };
}

sushi::FilledRectColorFix::FilledRectColorFix(IVec4 args, IVec4 color, int32_t z) : Rectangle(args.x, args.y, args.z, args.w, z)
{
	this->color = color;
}

sushi::FilledRectColorFix::~FilledRectColorFix()
{

}

const std::string sushi::FilledRectColorFix::getDetails()
{
	std::stringstream ss;
	ss << "x:" << this->pos.x << " y: " << this->pos.y << " z: " << this->pos.z << " r: " << this->color.x << " g: " << this->color.y << " b: " << this->color.z << " w: " << this->color.w;
	return std::string(ss.str());
}

void sushi::FilledRectColorFix::draw()
{
	//std::cout << "Draw: from FilledRectColorFix class" << std::endl;
}
