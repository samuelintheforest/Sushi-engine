#ifndef FILLED_RECT_TEXTURED_FIX_H
#define FILLED_RECT_TEXTURED_FIX_H

#include "Rectangle.h"
#include "Texture.h"

namespace sushi
{

	/*Todo*/

	class FilledRectTexturedFix : public Rectangle
	{
	public:
		FilledRectTexturedFix(IVec4 args, int32_t z, Vec4 txInfo, const Texture* tx);
		~FilledRectTexturedFix();
	protected:
		void addElement();
	private:
		Vec4 txAttrib;
		uint32_t txID;
		uint32_t txW;
		uint32_t txH;
	};


}

#endif
