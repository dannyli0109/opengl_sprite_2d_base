#pragma once
#include <vector>

#include "ShaderProgram.h"
#include "Texture.h"	
#include "Camera.h"
//#include "Graphics.h"

struct SpriteVertex
{
	glm::vec3 position;
	glm::vec2 uv;
	glm::vec4 color;
	glm::vec2 tiling;
	float textureIndex;
};

class SpriteRenderer
{
public:
	SpriteRenderer(ShaderProgram* shaderProgram, Camera* camera, int batchSize);
	~SpriteRenderer();
	void Begin(ShaderProgram* shaderProgram, Camera* camera);
	void End();
	void AddSprite(glm::mat4 transform, Texture* texture, glm::vec4 tint, glm::vec2 tiling, bool flipped);
private:
	ShaderProgram* shaderProgram;
	Camera* camera;
	GLuint vertexBuffer, indexBuffer, vao;
	int maxIndices, maxVertices, maxTextures, indexCount, vertexCount, textureCount;
	std::vector<SpriteVertex> vertices;
	std::vector<Texture*> textures;
	glm::vec4 quadPositions[4] = {
		{-0.5f, 0.5f, 0, 1.0f},
		{0.5f, 0.5f, 0, 1.0f},
		{-0.5f, -0.5f, 0, 1.0f},
		{0.5f, -0.5f, 0, 1.0f}
	};

	glm::vec2 quadUvs[4] = {
		{0, 0},
		{1, 0},
		{0, 1},
		{1, 1}
	};
};

