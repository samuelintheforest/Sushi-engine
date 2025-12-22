#ifndef FILLED_RECT_COLOR_DYN
#define	FILLED_RECT_COLOR_DYN


#include "Rectangle.h"

namespace sushi
{

	/*todo*/

	class FilledRectColorDyn : public Rectangle
	{
	public:
		FilledRectColorDyn();
		FilledRectColorDyn(IVec4 args, IVec4 color, int32_t z );
		~FilledRectColorDyn();

		void render();

	protected:
		IVec4 color;
	private:
		void addElement();

		
	};

}


#endif // !FILLED_RECT_COLOR_DYN
