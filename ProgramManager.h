#pragma once
#include "Graphics.h"
#include "GUI.h"
#include "ResourceManager.h"
#include "SpriteRenderer.h"
#include "Camera.h"
#include "Entity.h"
#include "Transform.h"
#include "SpriteContainer.h"
#include "SpriteAnimation.h"
#include "PlayerInputManager.h"

class ProgramManager
{
public:
	bool Init();
	void Run();
	void Destroy();
private:
	GLFWwindow* window;
	void RenderGUI();
	ResourceManager* resourceManager;
	SpriteRenderer* spriteRenderer;
	ShaderProgram* shader;
	Camera* camera;
	Entity* player;
	float time;
	float currentTime;
	float deltaTime;
};

