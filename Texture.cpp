#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Texture::Texture(std::string fileName)
{
	int width;
	int height;
	int channels;

	unsigned char* data = stbi_load(fileName.c_str(), &width, &height, &channels, 4);
	glGenTextures(1, &id);
	glBindTexture(GL_TEXTURE_2D, id);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		loadedSuccessfully = true;
		std::cout << "Loaded " << fileName << std::endl;
	}
	else {
		std::cout << "Fail to load texture" << std::endl;
		loadedSuccessfully = false;
	}

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glBindTexture(GL_TEXTURE_2D, 0);

	if (!loadedSuccessfully)
	{
		glDeleteTextures(1, &id);
	}
	
	stbi_image_free(data);
}

Texture::~Texture()
{
	if (loadedSuccessfully)
	{
		glDeleteTextures(1, &id);
	}
}

void Texture::Bind(int index)
{
	glBindTextureUnit(index, id);
}
