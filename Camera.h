#pragma once

#include <glm/glm.hpp>

class Camera
{
public:
	void init(int w, int h);
	void setModel(const glm::mat4x4& m);
	void setView(const glm::mat4x4& m);
	void getTransform(glm::mat4x4& m);
	void update();
private:
	glm::mat4x4 model;
	glm::mat4x4 view;
	glm::mat4x4 projection;
	glm::mat4x4 transform;
};
