#pragma once
#include <string>
#include <iostream>
#include "Graphics.h"

class Texture
{
public:
	Texture(std::string fileName);
	~Texture();
	void Bind(int index);
	GLuint GetId() { return id; }
private:
	GLuint id;
	bool loadedSuccessfully;
};

