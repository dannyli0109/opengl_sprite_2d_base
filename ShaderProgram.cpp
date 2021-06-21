#include "ShaderProgram.h"

ShaderProgram::ShaderProgram(std::string vertexFilename, std::string fragmentFilename)
{
	loadedSuccessfully = true;

	// TODO Shader can be abstract
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

	shaderProgram = glCreateProgram();

	std::string vertexSource = LoadFileAsString(vertexFilename);
	std::string fragmentSource = LoadFileAsString(fragmentFilename);

	const char* vertexSourceC = vertexSource.c_str();

	glShaderSource(vertexShader, 1, &vertexSourceC, nullptr);
	glCompileShader(vertexShader);

	GLchar errorLog[512];
	GLint success = 0;
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//Something failed with the vertex shader compilation
		std::cout << "Vertex shader " << vertexFilename << " failed with error:" << std::endl;
		glGetShaderInfoLog(vertexShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		loadedSuccessfully = false;
	}
	else
	{
		std::cout << "\"" << vertexFilename << "\" compiled successfully." << std::endl;
	}

	const char* fragmentSourceC = fragmentSource.c_str();

	glShaderSource(fragmentShader, 1, &fragmentSourceC, nullptr);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		//Something failed with the fragment shader compilation
		std::cout << "Fragment shader " << fragmentFilename << " failed with error:" << std::endl;
		glGetShaderInfoLog(fragmentShader, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		loadedSuccessfully = false;
	}
	else
	{
		std::cout << "\"" << fragmentFilename << "\" compiled successfully." << std::endl;
	}

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		std::cout << "Error linking shaders \"" << vertexFilename << "\" and \"" << fragmentFilename << "\"" << std::endl;
		glGetProgramInfoLog(shaderProgram, 512, nullptr, errorLog);
		std::cout << errorLog << std::endl;
		loadedSuccessfully = false;
	}


	if (loadedSuccessfully)
	{
		std::cout << "It appears that things are pretty okay" << std::endl;
	}
	else
	{
		//If there was a problem, tell OpenGL that we don't need those resources after all.
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
	}
}

ShaderProgram::~ShaderProgram()
{
	if (loadedSuccessfully)
	{
		glDeleteShader(vertexShader);
		glDeleteShader(fragmentShader);
		glDeleteProgram(shaderProgram);
	}
}

void ShaderProgram::UseShader()
{
	glUseProgram(shaderProgram);
}

void ShaderProgram::SetUniform(std::string varName, float value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform1f(varLoc, value);
}

void ShaderProgram::SetUniform(std::string varName, int value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform1i(varLoc, value);
}

void ShaderProgram::SetUniform(std::string varName, bool value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform1i(varLoc, value);
}

void ShaderProgram::SetUniform(std::string varName, glm::vec3 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform3f(varLoc, value.x, value.y, value.z);
}

void ShaderProgram::SetUniform(std::string varName, glm::vec2 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniform2f(varLoc, value.x, value.y);
}

void ShaderProgram::SetUniform(std::string varName, glm::mat4 value)
{
	GLuint varLoc = glGetUniformLocation(shaderProgram, varName.c_str());
	UseShader();
	glUniformMatrix4fv(varLoc, 1, GL_FALSE, &value[0][0]);
}
