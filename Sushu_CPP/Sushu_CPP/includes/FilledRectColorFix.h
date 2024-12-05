#ifndef FILLED_RECT_COLOR_FIX_H
#define FILLED_RECT_COLOR_FIX_H

#include "Rectangle.h"

namespace sushi
{

	class FixedRectColorFix : public Rectangle
	{
	public:
		FixedRectColorFix();
		~FixedRectColorFix();

		void draw() override;
	private:
		
	};


}

#endif
