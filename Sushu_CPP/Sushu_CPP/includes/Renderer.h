
#ifndef RENDERER_H
#define RENDERER_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glad/glad.h>
#include <vector>
#include <iostream>
#include "Shader.h"
#include "Scene.h"
#include <algorithm>    
#include <random>
#include <GLFW/glfw3.h>
#include <deque>


namespace sushi {
	class Renderer
	{
	public:
		unsigned int maxBatch;
		Shader* shader;
		unsigned int numOfQuads;
		unsigned int staticNumOfQuads;
		sushi::SceneDescription* scene;

		Renderer(unsigned int batchLimit, Shader* shader, float* txIds, float* fontTxIds, sushi::SceneDescription *m_SceneDescINput);
		~Renderer(void);
		void staticBegin();
		void staticEnd();
		void begin();
		void end();
		void satic_render();
		void draw3d_EXP();
		void draw3d_EXP_Multi();
		void setScreenQuad();
		bool rect_rect_Intersection(int r1x, int r1y, int r1w, int r1h, int r2x, int r2y, int r2w, int r2h);
		bool rect_point_Intersection(int rx, int ry, int rw, int rh, int px, int py);
		void renderQuadColor(float x, float y, float z, float width, float height, float* color);
		// TODO: 

		/*

		*/

		void setBackColor(int r, int g, int b, bool depth);
		inline void setMatrix(const glm::mat4& view, const glm::mat4& proj)
		{
			shader->use();
			shader->setMat4("camera", view);
			shader->setMat4("projection", proj);
		}
		void setModelMatrix(const glm::mat4& model, const glm::mat4& view, const glm::mat4& proj);
		void destroy();

	private:
	
		typedef  struct {
			GLuint  count;
			GLuint  primCount;
			GLuint  first;
			GLuint  baseInstance;
		} DrawArraysIndirectCommand;

		typedef  struct {
			GLuint  count;
			GLuint  primCount;
			GLuint  first;
			GLint   baseVertex;
			GLuint  baseInstance;
		} DrawElementsIndirectCommand;

		struct SVertex3D 
		{
			float x, y, z;
			float r, g, b;
		};
		int number_of_cubes = 1100;
		
		int number_of_spheres = number_of_cubes +1;
		glm::mat4* matrices = new glm::mat4[number_of_spheres + number_of_cubes];
		SVertex3D* vVertex = new SVertex3D[number_of_spheres * 2880 + number_of_cubes * 8];
		DrawElementsIndirectCommand* vDrawCommand = new DrawElementsIndirectCommand[number_of_spheres + number_of_cubes];
		GLuint* vDrawId = new GLuint[number_of_spheres + number_of_cubes];
		glm::vec3* position = new glm::vec3[number_of_spheres + number_of_cubes];
		
		GLuint ssbo;
		unsigned int rVao;
		unsigned int rVbo;
		unsigned int rEbo;
		GLuint rDrawIdBuffer;
		GLuint rIndirectBuffer;
		std::vector<float> verticesArray;
		unsigned int* indices;
		int indicesOffset;
		int realIndicesCount;
		int staticRealIndicesCount;

		void* staticMemoryPtr = NULL;

		float texCoords[4];
		float tmp = 0.0f;
		void setUp();
		void mapMemory();
		void setUp_EXP_3d();
		void setUp_EXP_Multi_3d();
	};
}
#endif // !RENDERER_H
