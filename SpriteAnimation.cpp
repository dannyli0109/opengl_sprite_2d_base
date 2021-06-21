#include "SpriteAnimation.h"

SpriteAnimation::SpriteAnimation(std::unordered_map<std::string, Animation> animations, std::string state)
{
	this->animations = animations;
	this->state = state;
	this->previousState = previousState;
}

void SpriteAnimation::Update(float deltaTime)
{
	frameTime += deltaTime;
	previousState = state;
	Transform* transform = entity->transform;

	if (state != previousState) frameTime = 0;

	Animation animation = animations[state];
	float animationTime = fmod(frameTime, animation.duration) / animation.duration;
	float animationFrame = MapVal(animationTime, 0, 1.0f, 0, animation.frameCount);

	SpriteContainer* spriteContainer = entity->GetComponent<SpriteContainer>();
	if (spriteContainer)
	{
		spriteContainer->sprite.texture = animation.textures[animationFrame];
		spriteContainer->sprite.tint = animation.tint;
		spriteContainer->sprite.tiling = animation.tiling;
		spriteContainer->sprite.flipped = animation.flipped;
	}
}
