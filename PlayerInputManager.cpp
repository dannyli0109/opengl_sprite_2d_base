#include "PlayerInputManager.h"

PlayerInputManager::PlayerInputManager(GLFWwindow* window)
{
	this->window = window;
}

void PlayerInputManager::Update(float deltaTime)
{
	SpriteAnimation* spriteAnimation = entity->GetComponent<SpriteAnimation>();
	bool moved = false;
	if (glfwGetKey(window, GLFW_KEY_W))
	{
		spriteAnimation->SetState("running_n");
		moved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_A))
	{
		spriteAnimation->SetState("running_w");
		moved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_S))
	{
		spriteAnimation->SetState("running_s");
		moved = true;
	}

	if (glfwGetKey(window, GLFW_KEY_D))
	{
		spriteAnimation->SetState("running_e");
		moved = true;
	}


	if (!moved)
	{
		std::string state = spriteAnimation->GetState();
		if (state == "running_s") spriteAnimation->SetState("idle_s");
		if (state == "running_n") spriteAnimation->SetState("idle_n");
		if (state == "running_e") spriteAnimation->SetState("idle_e");
		if (state == "running_w") spriteAnimation->SetState("idle_w");
	}
}
