#include "Camera.h"

Camera::Camera(glm::vec2 position, glm::vec2 windowSize, float zoom)
{
    this->position = position;
    this->windowSize = windowSize;
    this->zoom = zoom;
}

glm::mat4 Camera::GetProjection()
{
    float heightInTiles = windowSize.y / zoom;
    float widthInTiles = windowSize.x / zoom;
    glm::vec2 posAfterZoom = position / zoom;
    return glm::ortho(
        -widthInTiles / 2.0f + posAfterZoom.x,
        widthInTiles / 2.0f + posAfterZoom.x,
        -heightInTiles / 2.0f + posAfterZoom.y,
        heightInTiles / 2.0f + posAfterZoom.y, -1.0f, 1.0f);
}
