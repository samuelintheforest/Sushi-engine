#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "EssentialInlcudes.h"

// A glad.h tartalmazza az opengl-hez szükséges függvénymutatókat -> cross-platform
#include <glad/glad.h>
#include <GLFW/glfw3.h>


namespace sushi
{
	class Graphics
	{
	public:
		// Konstruktor és destruktor
		Graphics();
		~Graphics();

	private:
		void loadGraphicalLib();
	};
}

#endif // !GRAPHICS_H


