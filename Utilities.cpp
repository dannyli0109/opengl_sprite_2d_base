#include "Utilities.h"

std::string LoadFileAsString(std::string filename)
{
	std::stringstream fileSoFar;
	std::ifstream file(filename);

	if (file.is_open())
	{
		while (!file.eof())
		{
			std::string thisLine;
			std::getline(file, thisLine);
			fileSoFar << thisLine << std::endl;
		}
		return fileSoFar.str();
	}
	else
	{
		std::cout << "Error loading file: " << filename << std::endl;
		return "";
	}
}

float MapVal(float val, float v1min, float v1max, float v2min, float v2max)
{
	return ((val - v1min) * (v2max - v2min)) / (v1max - v1min) + v2min;
}

void LoadAnimationFrames(std::string folder, int count)
{
	ResourceManager* resourceManager = ResourceManager::GetInstance();
	for (int i = 0; i < count; i++)
	{
		std::string path;
		path += folder;
		path += "\\";
		path += "frame";
		path += std::to_string(i);
		path += ".png";
		resourceManager->AddTexture(new Texture(path));
	}
}
