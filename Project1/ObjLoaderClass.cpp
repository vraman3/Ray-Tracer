#include "ObjLoaderClass.h"

void ObjLoaderClass::readObjFile(std::string filename)
{
	std::string line;

	std::string temp = "./models/" + filename;

	std::cout << temp << std::endl;

	std::ifstream myfile(temp);
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

			if (name == "v")
			{
				float vertex[3];

				std::sscanf(line.c_str(), "%*s %f %f %f", &vertex[0], &vertex[1], &vertex[2]);

				//std::cout << "v1: " << vertex[0] << " v2: " << vertex[1] << " v3: " << vertex[2] << std::endl;
				vertices.push_back(vertex[0]);
				vertices.push_back(vertex[1]);
				vertices.push_back(vertex[2]);
			}
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

	for (int i = 0; i < vertices.size() / 3; i++)
	{
		opVertices.push_back(VectorClass(vertices[i], vertices[i + 1], vertices[i + 2]));
	}

}