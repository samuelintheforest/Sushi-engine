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

	private:
		void loadGraphicfuncsPtr();
	};
}

#endif // !GRAPHICS_H


