#include "Camera.h"
#include <glm/gtc/matrix_transform.hpp>

void Camera::init(int w, int h)
{
	model = glm::mat4x4(1.0f);
	view = glm::lookAt(glm::vec3(0.f, 0.f, 5.f), glm::vec3(0.f, 0.f, 0.f), glm::vec3(0.f, 1.f, 0.f));
	projection = glm::perspective(glm::radians(45.f), (float)h/w, 1.f, 1000.f);

	update();
}

void Camera::setModel(const glm::mat4x4& m)
{
	model = m;
}

void Camera::setView(const glm::mat4x4& m)
{
	view = m;
}

void Camera::getTransform(glm::mat4x4& m)
{
	m = transform;
}

void Camera::update()
{
	transform = projection * view * model;
}