#include "../includes/Rectangle.h"

sushi::Rectangle::Rectangle() : Entity()
{
	this->dim = { 0, 0 };
}

sushi::Rectangle::Rectangle(int32_t x, int32_t y, int32_t z, int32_t w, int32_t h) : Entity(x, y, z)
{
	this->dim = { w, h };
}

sushi::Rectangle::Rectangle(IVec3 pos, IVec2 dim) : Entity(pos.x, pos.y, pos.z)
{
	this->dim = dim;
}

sushi::Rectangle::~Rectangle()
{
	/*DESTROY OBJ*/
}

void sushi::Rectangle::draw()
{
	/*TODO*/
	std::cout << "Draw: from Rectangle class" << std::endl;
}
