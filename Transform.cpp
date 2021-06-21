#include "Transform.h"

Transform::Transform(glm::vec3 position, float rotation, glm::vec2 scale)
{
	localTransform = glm::mat4(1.0f);
	Scale(scale);
	Rotate(rotation);
	Translate(position);
}

void Transform::Translate(const glm::vec3& direction)
{
	localTransform = glm::translate(localTransform, direction);
}

void Transform::Rotate(float rad)
{
	localTransform = glm::rotate(localTransform, rad, glm::vec3(0, 0, 1.0f));
}

void Transform::Scale(const glm::vec2& scale)
{
	localTransform = glm::scale(localTransform, glm::vec3(scale, 1));
}

void Transform::Update(float deltaTime)
{
	Entity* parent = entity->GetParent();
	if (parent)
	{
		Transform* parentTransform = parent->GetComponent<Transform>();
		if (parentTransform)
		{
			globalTransform = parentTransform->globalTransform * localTransform;
		}
	}
	else
	{
		globalTransform = localTransform;
	}
}
