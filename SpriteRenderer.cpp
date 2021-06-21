#include "SpriteRenderer.h"

SpriteRenderer::SpriteRenderer(ShaderProgram* shaderProgram, Camera* camera, int batchSize)
{
	this->shaderProgram = shaderProgram;
	this->camera = camera;
	maxVertices = batchSize * 4;
	maxIndices = batchSize * 6;
	maxTextures = 32;

	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);
	glGenVertexArrays(1, &vao);

	vertices.resize(maxVertices);
	textures.resize(maxTextures);
	
	std::vector<unsigned short> indices;
	indices.resize(maxIndices);

	unsigned short offset = 0;

	for (int i = 0; i < maxIndices; i += 6)
	{
		indices[i + 0] = offset + 0;
		indices[i + 1] = offset + 1;
		indices[i + 2] = offset + 2;
		indices[i + 3] = offset + 1;
		indices[i + 4] = offset + 3;
		indices[i + 5] = offset + 2;
		offset += 4;
	}

	for (int i = 0; i < maxTextures; i++)
	{
		std::stringstream tex;
		tex << "u_Textures[" << i << "]";
		shaderProgram->SetUniform(tex.str(), i);
	}

	textureCount = 0;

	// Bind buffers
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, maxVertices * sizeof(SpriteVertex), nullptr, GL_DYNAMIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, maxIndices * sizeof(unsigned short), indices.data(), GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glBindVertexArray(vao);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, SpriteVertex::position));

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, SpriteVertex::uv));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, SpriteVertex::color));

	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, SpriteVertex::tiling));

	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 1, GL_FLOAT, GL_FALSE, sizeof(SpriteVertex), (const void*)offsetof(SpriteVertex, SpriteVertex::textureIndex));

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

SpriteRenderer::~SpriteRenderer()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vao);
}

void SpriteRenderer::Begin(ShaderProgram* shaderProgram, Camera* camera)
{
	this->shaderProgram = shaderProgram;
	this->camera = camera;

	indexCount = 0;
	vertexCount = 0;
	textureCount = 0;

	glm::mat4 proj = camera->GetProjection();

	shaderProgram->SetUniform("u_ProjectionMatrix", proj);
}

void SpriteRenderer::End()
{
	if (indexCount == 0) return;

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertexCount * sizeof(SpriteVertex), vertices.data());
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	for (int i = 0; i < textureCount; i++)
	{
		textures[i]->Bind(i);
	}

	glBindVertexArray(vao);
	glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_SHORT, 0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void SpriteRenderer::AddSprite(glm::mat4 transform, Texture* texture, glm::vec4 tint, glm::vec2 tiling, bool flipped)
{
	if (indexCount >= maxIndices)
	{
		End();
		Begin(shaderProgram, camera);
	}

	int textureIndex = -1;
	for (int i = 0; i < textureCount; i++)
	{
		if (texture->GetId() == textures[i]->GetId())
		{
			textureIndex = i;
			break;
		}
	}

	if (textureIndex == -1)
	{
		if (textureCount >= maxTextures)
		{
			End();
			Begin(shaderProgram, camera);
		}

		textureIndex = textureCount;
		textures[textureIndex] = texture;
		textureCount++;
	}

	for (int i = 0; i < 4; i++)
	{
		vertices[vertexCount].position = transform * quadPositions[i];
		vertices[vertexCount].uv = quadUvs[i];
		vertices[vertexCount].color = tint;
		vertices[vertexCount].textureIndex = textureIndex;
		vertices[vertexCount].tiling = tiling;

		if (flipped)
		{
			vertices[vertexCount].uv.x = 1 - vertices[vertexCount].uv.x;
		}
		vertexCount++;
	}
	indexCount += 6;
}
