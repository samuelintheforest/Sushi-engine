#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include "Types.h"

namespace sushi
{
	class Entity
	{
	public:
		Entity();
		Entity(uint32_t x, uint32_t y, uint32_t z);
		~Entity();

		virtual void draw();
		
	protected:
		IVec3 pos;
	private:
		
	};
}

#endif
