#ifndef FILLED_RECT_COLOR_FIX_H
#define FILLED_RECT_COLOR_FIX_H

#include "Rectangle.h"
#include "Types.h"

namespace sushi
{
	class FilledRectColorFix : public Rectangle
	{
	public:
		FilledRectColorFix();
		FilledRectColorFix(IVec4 args, IVec4 color, int32_t z );
		~FilledRectColorFix();

		void getDesc(FilledRectColorFixDesc& rectDesc);
	protected:
		IVec4 color;
	private:
		void addElement();
	};


}

#endif
