#pragma once
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include "ResourceManager.h"


std::string LoadFileAsString(std::string filename);
float MapVal(float val, float v1min, float v1max, float v2min, float v2max);
void LoadAnimationFrames(std::string folder, int count);