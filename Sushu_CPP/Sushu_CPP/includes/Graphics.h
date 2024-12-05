#ifndef GRAPHICS_H
#define GRAPHICS_H


#include "GLShader.h"
#include "FilledRectColorFix.h"

#include "../../../vendor/include/GLFW/glfw3.h"
#include <iostream>
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

		void addNewfixFilledRect(FilledRectColorFixDesc* rect);
		void setUpSGXVertexMisc();
		void setSGXUniformMatrices(const Mat4& model, const Mat4& view, const Mat4& proj);
		void renderSGXfixFilledRects();
		void clearSGXScreen(float r, float g, float b, float w);

	private:
		void loadSGXfuncsPtr();
		void compileSGXShaders();


		/* Shader pointers */
		GLShader* FilledRectColorFixShader;
		GLShader* FilledRectColorDynShader;
		GLShader* FilledRectTexturedFixShader;
		GLShader* FilledRectTexturedDynShader;

		/* Containers, Counters, and GLobjects - FilledRectColorFix */
		std::vector<float> fixFilledRectVertices;
		std::vector<uint32_t> fixFilledRectIndices;
		uint32_t fixFilledRectVerticesCnt;
		uint32_t fixFilledRectIndicesCnt;
		uint32_t fixFilledRectIndicesOffset;
		uint32_t fixFilledRectCnt;

		uint32_t fixFilledRectVAO;
		uint32_t fixFilledRectVBO;
		uint32_t fixFilledRectEBO;
		
	};
}

#endif // !GRAPHICS_H


