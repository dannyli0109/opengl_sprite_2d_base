#include "Entity.h"
#include "Transform.h"

Entity::Entity(Transform* transform)
{
	this->transform = transform;
	AddComponent(transform);
}

Entity::~Entity()
{
	for (Component* component : components)
	{
		delete component;
	}

	for (Entity* child : children)
	{
		delete child;
	}
}

void Entity::Update(float deltaTime)
{
	for (Component* component : components)
	{
		component->Update(deltaTime);
	}

	for (Entity* child : children)
	{
		child->Update(deltaTime);
	}
}

void Entity::Draw(SpriteRenderer* spriteRenderer)
{
	for (Component* component : components)
	{
		component->Draw(spriteRenderer);
	}

	for (Entity* child : children)
	{
		child->Draw(spriteRenderer);
	}
}

void Entity::AddChild(Entity* child)
{
	child->parent = this;
	children.push_back(child);
}

void Entity::RemoveChild(Entity* child)
{
	auto position = std::find(children.begin(), children.end(), child);
	if (position != children.end())
	{
		children.erase(position);
		child->parent = nullptr;
	}
}

void Entity::AddComponent(Component* component)
{
	components.push_back(component);
	component->SetEntity(this);
}

void Entity::RemoveComponent(Component* component)
{
	auto position = std::find(components.begin(), components.end(), component);
	if (position != components.end())
	{
		delete (*position);
		components.erase(position);
	}
}

Entity* Entity::GetParent()
{
	return parent;
}
