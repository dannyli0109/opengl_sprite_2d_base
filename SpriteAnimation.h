#pragma once
#include "Component.h"
#include "Texture.h"
#include <unordered_map>
#include "SpriteRenderer.h"
#include "Transform.h"
#include "SpriteContainer.h"

struct Animation
{
    std::vector<Texture*> textures;
    int frameCount;
    float duration;
    glm::vec4 tint = { 1.0f, 1.0f, 1.0f, 1.0f };
    glm::vec2 tiling = { 1.0f, 1.0f };
    bool flipped = false;
    int currentFrame = 0;
};
class SpriteAnimation :
    public Component
{
public:
    SpriteAnimation(
        std::unordered_map<std::string, Animation> animations,
        std::string state
    );
    virtual void Update(float deltaTime) override;
    virtual void Draw(SpriteRenderer* spriteRenderer) override {}
    void SetState(std::string state) { this->state = state; }
    std::string GetState() { return state; }

private:
    std::unordered_map<std::string, Animation> animations;
    std::string state;
    std::string previousState;
    float frameTime = 0.0f;
};

