#include "../includes/Entity.h"
#include "../includes/GameLogic.h"

sushi::Entity::Entity()
{
	this->pos = { 0, 0, 0 };
	addElement();
}

sushi::Entity::Entity(int32_t x, int32_t y, int32_t z)
{
	this->pos = { x, y, z };
	addElement();
}

sushi::Entity::~Entity()
{
	/*DESTROY OBJ*/
}

void sushi::Entity::draw()
{
	//std::cout << "Render entity" << std::endl;
}

inline void sushi::Entity::addElement()
{
	sushi::GameLogic::addtoScene(this);
}

