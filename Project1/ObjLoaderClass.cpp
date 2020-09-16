/**
	RayTracing, ObjectClass.cpp
	Read an object file (.obj) and parse it to get the information
	about all the triangles in the model.

	@author: Vishwanath Raman
	@version: 1.0 Oct/21/2017

*/
#include "ObjLoaderClass.h"

/**
	Read an object file (.obj) and store the vertices and faces for each triangle
	in the model.

	@param paramFilename: String name of the file. (e.g. thisThing.obj)
*/
void ObjLoaderClass::readObjFile(std::string paramFilename)
{
	std::string line;

	std::string relativePathFilename = "./models/" + paramFilename;

	std::ifstream myfile(relativePathFilename);
	std::string name;


	if (myfile.is_open())
	{/*
	 while (std::getline(myfile, line))
	 {*/

		while (std::getline(myfile, line))
		{
			if (line == "" || line[0] == '#')
			{
				continue;
			}
			std::istringstream linestream(line);
			linestream >> name;
			
			//
			// Store the vertices
			//
			if (name == "v")
			{
				float vertex[3];

				std::sscanf(line.c_str(), "%*s %f %f %f", &vertex[0], &vertex[1], &vertex[2]);

				//std::cout << "v1: " << vertex[0] << " v2: " << vertex[1] << " v3: " << vertex[2] << std::endl;
				vertices.push_back(vertex[0]);
				vertices.push_back(vertex[1]);
				vertices.push_back(vertex[2]);
			}
			//
			// Store the faces
			//
			else if (name == "f")
			{
				int face[3];

				std::sscanf(line.c_str(), "%*s %i %i %i", &face[0], &face[1], &face[2]);

				//std::cout << "f1: " << face[0] << " f2: " << face[1] << " f3: " << face[2] << std::endl;
				faces.push_back(face[0]);
				faces.push_back(face[1]);
				faces.push_back(face[2]);
			}
		}
		myfile.close();
	}
	else
		std::cout << "Unable to open file.";

	//
	// Store all the vertices currently in a flat array in a VectorClass.
	//
	for (int i = 0; i < vertices.size(); i += 3)
	{
		opVertices.push_back(VectorClass(vertices[i], vertices[i + 1], vertices[i + 2]));
	}

}