#ifndef ENTITY_H
#define ENTITY_H

#include "Types.h"

#include <iostream>



namespace sushi
{
	class Entity
	{
	public:
		Entity();
		Entity(int32_t x, int32_t y, int32_t z);
		~Entity();

		virtual void draw();
		
		
	protected:
		IVec3 pos;
		virtual void addElement();
	private:
		
	};
}

#endif
