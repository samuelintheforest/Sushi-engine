#ifndef GRAPHICS_H
#define GRAPHICS_H


#include "../../../vendor/include/glad/glad.h"
#include "../../../vendor/include/GLFW/glfw3.h"
#include "Shader.h"

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
		inline void setSGXViewport(int32_t x, int32_t y, int32_t w, int32_t h);

	private:
		void loadSGXfuncsPtr();
		void compileSGXShaders();


		Shader* FilledRectColorFixShader;
		Shader* FilledRectColorDynShader;
		Shader* FilledRectTexturedFixShader;
		Shader* FilledRectTexturedDynShader;
	};
}

#endif // !GRAPHICS_H


