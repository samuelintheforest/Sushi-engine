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
		// Konstruktor �s destruktor
		Graphics(uint32_t maxDynRect);
		~Graphics();

		void enableSGXDepth();
		void disableSGXDepth();
		void setSGXViewport(int32_t x, int32_t y, int32_t w, int32_t h);
		void setUpSGXFixVertexMisc();
		void setUpSGXDynVertexMisc();
		void setSGXUniformMatrices(const Mat4& model, const Mat4& view, const Mat4& proj);
		void renderSGXfixFilledRects();
		void clearSGXScreen(uint8_t r, uint8_t g, uint8_t b, uint8_t w);
		void SGXFinishOperation();
		void setDynRectCount(uint32_t number);
		void resetDynRectBuffer();
		uint32_t getDynRectCount();

		void setSGXViewMatrix(const Mat4 &view);
		Mat4& getSGXViewMatrix();

		void setSGXModelMatrix(const Mat4 &model);
		Mat4& getSGXModelMatrix();

		void setSGXProjectionMatrix(const Mat4 &proj);
		Mat4& getSGXProjectionMatrix();

		/* Containers, Counters, and GLobjects - FilledRectColorFix */
		std::vector<float> fixFilledRectVertices;
		std::vector<float> fixFilledRectVerticesTransparent;
		std::vector<uint32_t> fixFilledRectIndices;
		std::vector<uint32_t> textureSlot;

		std::vector<float> dynamicFilledRectVertices;
		std::vector<float> dynamicFilledRectVerticesTransparent;
		std::vector<uint32_t> dynamicFilledRectIndices;

		

	private:
		void loadSGXfuncsPtr();
		void enableSGXBlending();
		void compileSGXShaders();

		void configureFixOpaqueColourRectsSGX();
		void configureFixTransparentColourRectsSGX();
		void configureFixTransparentTextureRectsSGX();

		void configureDynOpaqueColourRectsSGX();
		void configureDynTransparentColourRectsSGX();
		void configureDynTransparentTextureRectsSGX();

		void initDynFilledRectIndicesBuffer();
		void bindTextures();
		void updateDynVBO();

		/* Shader pointers */
		SGXShader* FilledRectFixShader;
		SGXShader* FilledRectColorDynShader;
		SGXShader* FilledRectTexturedDynShader;

		uint32_t fixFilledRectVAO;
		uint32_t fixFilledRectVBO;
		uint32_t fixFilledRectEBO;

		uint32_t dynFilledRectVAO;
		uint32_t dynFilledRectVBO;
		uint32_t dynFilledRectEBO;

		Mat4 FilledRectFixModelM4 = Mat4(1.0f);
		Mat4 FilledRectFixViewM4 = Mat4(1.0f);
		Mat4 FilledRectFixProjectionM4 = Mat4(1.0f);

		uint32_t maxDynRect;
		uint32_t dynRectCount;
		
	};
}

#endif // !GRAPHICS_H


