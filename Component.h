#pragma once
#include "SpriteRenderer.h"

class Entity;
class Component
{
public:
	Component() = default;
	virtual ~Component() {}
	Entity* GetEntity() { return entity; }
	void SetEntity(Entity* entity) { this->entity = entity; }
	virtual void Update(float deltaTime) = 0;
	virtual void Draw(SpriteRenderer* spriteRenderer) = 0;
protected:
	Entity* entity;
};

