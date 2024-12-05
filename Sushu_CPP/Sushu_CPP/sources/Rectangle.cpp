#include "../includes/Rectangle.h"

sushi::Rectangle::Rectangle()
{
	this->pos = { 0, 0, 0 };
	this->dim = { 0, 0 };
}

sushi::Rectangle::Rectangle(uint32_t x, uint32_t y, uint32_t z, uint32_t w, uint32_t h)
{
	this->pos = { x, y, z };
	this->dim = { w, h };
}

sushi::Rectangle::Rectangle(IVec3 pos, IVec2 dim)
{
	this->pos = pos;
	this->dim = dim;
}

sushi::Rectangle::~Rectangle()
{

}

void sushi::Rectangle::draw()
{
	/*TODO*/
	std::cout << "Draw: from Rectangle class" << std::endl;
}
