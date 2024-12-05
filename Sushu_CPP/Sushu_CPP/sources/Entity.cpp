#include "../includes/Entity.h"

sushi::Entity::Entity()
{
	this->pos = { 0, 0, 0 };
}

sushi::Entity::Entity(uint32_t x, uint32_t y, uint32_t z)
{
	this->pos = { x, y, z };
}

sushi::Entity::~Entity()
{
}
