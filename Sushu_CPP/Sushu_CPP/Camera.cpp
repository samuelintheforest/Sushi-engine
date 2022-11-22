#include "Camera.h"

Sushi::Camera::Camera(int type, float radius)
{
	m_cameraRadius = radius;
}

Sushi::Camera::~Camera()
{
}

glm::mat4 Sushi::Camera::calculateViewMatrix()
{
	return glm::mat4();
}

void Sushi::Camera::setupOrbitCamera()
{
}
