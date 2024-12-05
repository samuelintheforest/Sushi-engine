#ifndef GRAPHICS_H
#define GRAPHICS_H


#include "../../../vendor/include/glad/glad.h"
#include "../../../vendor/include/GLFW/glfw3.h"
#include <iostream>

namespace sushi
{
	class Graphics
	{
	public:
		// Konstruktor és destruktor
		Graphics();
		~Graphics();

		inline void enableSGXDepth();
		inline void disableSGXDepth();
		inline void setSGXViewport(uint32_t x, uint32_t y, uint32_t w, uint32_t h);

	private:
		void loadSGXfuncsPtr();
	};
}

#endif // !GRAPHICS_H


