#pragma once
#include <vector>
#include "Component.h"
//#include "Transform.h"
class Transform;
class Entity
{
public:
	Entity(Transform* transform);
	virtual ~Entity();
	virtual void Update(float deltaTime);
	virtual void Draw(SpriteRenderer* spriteRenderer);
	void AddChild(Entity* child);
	void RemoveChild(Entity* child);
	void AddComponent(Component* component);
	void RemoveComponent(Component* component);
	Entity* GetParent();
	template<typename T>
	T* GetComponent()
	{
		for (Component* component : components)
		{
			if (dynamic_cast<T*>(component) != nullptr)
			{
				return dynamic_cast<T*>(component);
			}
		}
		return nullptr;
	}
public:
	Transform* transform = nullptr;
private:
	std::vector<Entity*> children;
	std::vector<Component*> components;
	Entity* parent = nullptr;
};

