#pragma once
#include "Component.h"
#include "Entity.h"
#include "Transform.h"

struct Sprite
{
    Texture* texture;
    glm::vec4 tint;
    glm::vec2 tiling;
    bool flipped;
};

class SpriteContainer :
    public Component
{
public:
    SpriteContainer(Sprite sprite);
    void Update(float deltaTime) override {}
    void Draw(SpriteRenderer* spriteRenderer) override;
    Sprite sprite;

};

