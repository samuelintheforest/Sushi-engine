#ifndef ENTITY_H
#define ENTITY_H

#include <cstdint>
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

		struct IVec3 pos;

	private:

	};
}

#endif
