#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <sstream>

class ObjLoaderClass
{
	public:
		std::vector<float> vertices;
		std::vector<int> faces;
		std::vector<VectorClass> opVertices;
		ObjLoaderClass(){};

		void readObjFile(std::string filenameWExt);
};

