#pragma once
#include "Graphics.h"
class Camera
{
public:
	Camera(glm::vec2 position, glm::vec2 windowSize, float zoom);
	glm::mat4 GetProjection();
private:
	glm::vec2 position;
	glm::vec2 windowSize;
	float zoom;
};

