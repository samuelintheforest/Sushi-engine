#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "../../../vendor/include/glm/glm.hpp"
#include "../../../vendor/include/glm/gtc/matrix_transform.hpp"
#include "../../../vendor/include/glm/gtc/type_ptr.hpp"
#include "../../../vendor/include/glad/glad.h"

namespace sushi {

	class Camera 
	{
	public:
		#define ORBIT 0
		#define FLYER 1

		float m_cameraRadius;

		Camera(int type, float radius);
		~Camera();
		glm::mat4 calculateViewMatrix();


	private:
		void setupOrbitCamera();


	};

}

#endif // !CAMERA_H
