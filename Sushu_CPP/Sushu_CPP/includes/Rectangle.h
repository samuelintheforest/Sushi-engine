#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Entity.h"
#include "Types.h"

namespace sushi
{

	class Rectangle : public Entity
	{
	public:
		Rectangle();
		Rectangle(uint32_t x, uint32_t y, uint32_t z, uint32_t w, uint32_t h);
		Rectangle(IVec3 pos, IVec2 dim);
		~Rectangle();
		void draw() override;
	protected:
		IVec2 dim;

	private:
		
	};

}

#endif
