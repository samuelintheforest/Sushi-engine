#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLShader.h"
#include "FilledRectColorFix.h"


#include <iostream>
#include <sstream>
#include <vector>


namespace sushi
{
	constexpr float colorRatio = 1.0f / 255.0f;

	class Graphics
	{
	public:
		// Konstruktor és destruktor
		Graphics();
		~Graphics();

		void enableSGXDepth();
		void disableSGXDepth();
		void setSGXViewport(int32_t x, int32_t y, int32_t w, int32_t h);

		void setUpSGXVertexMisc();
		void setSGXUniformMatrices(const Mat4& model, const Mat4& view, const Mat4& proj);
		void renderSGXfixFilledRects();
		void clearSGXScreen(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
		void SGXFinishOperation();

		/* Containers, Counters, and GLobjects - FilledRectColorFix */
		std::vector<float> fixFilledRectVertices;
		std::vector<uint32_t> fixFilledRectIndices;
		std::vector<uint32_t> textureSlot;

	private:
		void loadSGXfuncsPtr();
		void enableSGXBlending();
		void compileSGXShaders();


		/* Shader pointers */
		SGXShader* FilledRectFixShader;
		SGXShader* FilledRectColorDynShader;
		SGXShader* FilledRectTexturedDynShader;

		uint32_t fixFilledRectVAO;
		uint32_t fixFilledRectVBO;
		uint32_t fixFilledRectEBO;

		Mat4 FilledRectFixModelM4 = Mat4(1.0f);
		Mat4 FilledRectFixViewM4 = Mat4(1.0f);
		Mat4 FilledRectFixProjectionM4 = Mat4(1.0f);
		
	};
}

#endif // !GRAPHICS_H


