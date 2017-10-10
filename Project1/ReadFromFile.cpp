/**
	RayTracing, ReadFromFile.cpp
	Class file to implement reading from a BMP file.

	@author: Vishwanath Raman
	@version: 1.0 Oct/10/2017

*/

#include "ReadFromFile.h"

/**
	Set the width of the image.

	@param paramW: The width to be set.
*/
void ReadFromFile::SetWidth(int paramW)
{
	width = paramW;
}

/**
	Set the height of the image.

	@param paramH: The height to be set.
*/
void ReadFromFile::SetHeight(int paramH)
{
	height = paramH;
}

/**
	Get the width of the image.

	@return the width of the current image.
*/
int ReadFromFile::GetWidth()
{
	return width;
}

/**
	Get the height of the image.

	@return the height of the current image.
*/
int ReadFromFile::GetHeight()
{
	return height;
}

/**
	Read from a .BMP file.

	@param *filename: Name of the file to be read.
	@return the data for all colour values for each pixel in the file read.
*/
ColourClass* ReadFromFile::ReadBMP(char* filename)
{
	FILE* f = fopen(filename, "rb");

	if (f == NULL)
		throw "Argument Exception";

	unsigned char info[54];
	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header

	// extract image height and width from header
	int width = *(int*)&info[18];
	int height = *(int*)&info[22];

	SetWidth(width);
	SetHeight(height);
	ColourClass *testerC = new ColourClass[width*height];

	std::cout << std::endl;
	std::cout << "Name: " << filename << std::endl;
	std::cout << "Width: " << width << std::endl;
	std::cout << "Height: " << height << std::endl;

	int row_padded = (width * 3 + 3) & (~3);
	unsigned char* data = new unsigned char[row_padded];
	unsigned char tmp;

	int testCounter = 0;
	int start = 0;

	//ColourClass* dimensionTest[][] = new ColourClass[width][];
	for (int i = 0; i < height; i++)
	{
		fread(data, sizeof(unsigned char), row_padded, f);
		for (int j = 0; j < width * 3; j += 3)
		{
			// Convert (B, G, R) to (R, G, B)
			tmp = data[j];
			data[j] = data[j + 2];
			data[j + 2] = tmp;

			//if (testCounter < 20)
			//{
			//	//std::cout << "R: " << (int)data[j] << " G: " << (int)data[j + 1] << " B: " << (int)data[j + 2] << std::endl;
			//	testCounter++;
			//}
			double r, g, b;
			r = (int)data[j];
			g = (int)data[j + 1];
			b = (int)data[j + 2];

			testerC[start].SetRed(r / 255);

			testerC[start].SetGreen(g / 255);
			testerC[start].SetBlue(b / 255);


			if (testCounter < 20)
			{
				//std::cout << testerC[start].GetRed() << " " << testerC[start].GetGreen() << " " << testerC[start].GetBlue() << std::endl;
				//std::cout << r << " " << g << " " << b << std::endl;
				testCounter++;
			}

			// DO NOT COMMENT THIS
			start++;
		}
	}

	fclose(f);
	//return data;
	delete data;
	return testerC;
}

////class ReadFromFile
////{
//unsigned char* readBMP(char* filename)
//{
//	int i;
//	FILE* f = fopen(filename, "rb");
//	unsigned char info[54];
//	fread(info, sizeof(unsigned char), 54, f); // read the 54-byte header
//
//	// extract image height and width from header
//	int width = *(int*)&info[18];
//	int height = *(int*)&info[22];
//
//	int size = 3 * width * height;
//	unsigned char* data = new unsigned char[size]; // allocate 3 bytes per pixel
//	fread(data, sizeof(unsigned char), size, f); // read the rest of the data at once
//	fclose(f);
//
//	for (i = 0; i < size; i += 3)
//	{
//		unsigned char tmp = data[i];
//		data[i] = data[i + 2];
//		data[i + 2] = tmp;
//	}
//
//	return data;
//}
////};