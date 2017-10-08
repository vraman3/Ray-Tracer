#pragma once

#include "VectorClass.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>
#include <vector>

class ObjLoaderClass
{
	public:
		std::vector<float> vertices;
		std::vector<int> faces;
		std::vector<VectorClass> opVertices;
		ObjLoaderClass(){};

		void readObjFile(std::string filenameWExt);
};

