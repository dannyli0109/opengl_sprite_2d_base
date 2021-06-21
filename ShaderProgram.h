#pragma once
#include "Utilities.h"
#include "Graphics.h"

class ShaderProgram
{
public:
	ShaderProgram(std::string vertexFilename, std::string fragmentFilename);
	~ShaderProgram();
	
	void UseShader();

	void SetUniform(std::string varName, float value);
	void SetUniform(std::string varName, int value);
	void SetUniform(std::string varName, bool value);
	void SetUniform(std::string varName, glm::vec3 value);
	void SetUniform(std::string varName, glm::vec2 value);
	void SetUniform(std::string varName, glm::mat4 value);
private:
	GLuint vertexShader, fragmentShader, shaderProgram;
	bool loadedSuccessfully;
};

