/**
	RayTracing, ObjLoaderClass.h
	Header file to implement ObjLoaderClass.

	@author: Vishwanath Raman
	@version: 1.0 Oct/21/2017

*/
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
		/* Variables */
		std::vector<float> vertices;
		std::vector<int> faces;
		std::vector<VectorClass> opVertices;

		/* Constructors */
		ObjLoaderClass(){};

		/* Methods */
		void readObjFile(std::string filenameWExt);
};

