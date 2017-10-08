#pragma once

//Author: Vishwanath Raman
/**
This function to read from a 24 bit BMP file was built upon a question on stackoverflow

Code:http://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file
**/
#include<iostream>
#include<fstream>

#include "ColourClass.h"

//unsigned char* ReadBMP(char* filename)
class ReadFromFile
{
private:
	int width, height;

public:
	void SetWidth(int w);
	void SetHeight(int h);

	int GetWidth();
	int GetHeight();

	ColourClass* ReadBMP(char* filename);

};

