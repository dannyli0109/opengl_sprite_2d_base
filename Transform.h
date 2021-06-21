#pragma once
#include "Component.h"
#include "Entity.h"
class Transform :
    public Component
{
public:
    Transform(glm::vec3 position, float rotation, glm::vec2 scale);
    void Translate(const glm::vec3& direction);
    void Rotate(float deg);
    void Scale(const glm::vec2& scale);
    void Update(float deltaTime) override;
    void Draw(SpriteRenderer* spriteRenderer) override {}
    glm::mat4 GetTransformMatrix() { return globalTransform; }
private:
    glm::mat4 globalTransform;
    glm::mat4 localTransform;
};

