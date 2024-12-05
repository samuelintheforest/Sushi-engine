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
		Rectangle(int32_t x, int32_t y, int32_t z, int32_t w, int32_t h);
		Rectangle(IVec3 pos, IVec2 dim);
		~Rectangle();
		void draw();
	protected:
		IVec2 dim;
		void addElement();
	private:
		
	};

}

#endif
