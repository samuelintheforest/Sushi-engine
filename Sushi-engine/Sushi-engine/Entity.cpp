#include "GameLogic.h"
#include "Entity.h"


sushi::Entity::Entity()
{
	this->pos = { 0, 0, 0 };
}

sushi::Entity::Entity(int32_t x, int32_t y, int32_t z)
{
	this->pos = { x, y, z };
}

sushi::Entity::~Entity()
{
	/*DESTROY OBJ*/
}

void sushi::Entity::addElement()
{
	sushi::GameLogic::addtoScene(this);
	std::cout << "Added entity" << std::endl;
}

