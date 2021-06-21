#include "SpriteContainer.h"

SpriteContainer::SpriteContainer(Sprite sprite)
{
	this->sprite = sprite;
}

void SpriteContainer::Draw(SpriteRenderer* spriteRenderer)
{
	Transform* transform = entity->transform;
	glm::mat4 transformMatrix = transform->GetTransformMatrix();
	spriteRenderer->AddSprite(transformMatrix, sprite.texture, sprite.tint, sprite.tiling, sprite.flipped);
}
