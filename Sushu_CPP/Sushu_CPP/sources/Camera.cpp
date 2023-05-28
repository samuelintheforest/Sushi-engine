#include "..\includes\Camera.h"

sushi::Camera::Camera(int type, float radius)
{
	m_cameraRadius = radius;
}

sushi::Camera::~Camera()
{
}

glm::mat4 sushi::Camera::calculateViewMatrix()
{
	return glm::mat4();
}

void sushi::Camera::setupOrbitCamera()
{
}
