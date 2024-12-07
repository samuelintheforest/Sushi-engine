#ifndef GRAPHICS_H
#define GRAPHICS_H


#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "GLShader.h"
#include "FilledRectColorFix.h"


#include <iostream>
#include <sstream>
#include <vector>

#include "Types.h"

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
		uint32_t fixFilledRectVerticesCnt;
		uint32_t fixFilledRectIndicesCnt;
		uint32_t fixFilledRectIndicesOffset;
		uint32_t fixFilledRectCnt;

	private:
		void loadSGXfuncsPtr();
		void compileSGXShaders();


		/* Shader pointers */
		GLShader* FilledRectColorFixShader;
		GLShader* FilledRectColorDynShader;
		GLShader* FilledRectTexturedFixShader;
		GLShader* FilledRectTexturedDynShader;

		uint32_t fixFilledRectVAO;
		uint32_t fixFilledRectVBO;
		uint32_t fixFilledRectEBO;

		Mat4 FilledRectColorFixModelM4 = Mat4(1.0f);
		Mat4 FilledRectColorFixViewM4 = Mat4(1.0f);
		Mat4 FilledRectColorFixProjectionM4 = Mat4(1.0f);
		
	};
}

#endif // !GRAPHICS_H


