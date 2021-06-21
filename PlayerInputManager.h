#pragma once
#include "Component.h"
#include "SpriteRenderer.h"
#include "SpriteAnimation.h"

class PlayerInputManager :
    public Component
{
public:
    PlayerInputManager(GLFWwindow* window);
    virtual void Update(float deltaTime) override;
    virtual void Draw(SpriteRenderer* spriteRenderer) override {}
private:
    GLFWwindow* window;
};

