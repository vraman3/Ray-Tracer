/**
	RayTracing, ReadFromFile.h
	Header file for the ReadFromFile class

	@author: This function to read from a 24 bit BMP file was built upon a question on stackoverflow
			 Code:http://stackoverflow.com/questions/9296059/read-pixel-value-in-bmp-file
	@version: 1.0 Oct/10/2017

*/

#pragma once

#include<iostream>
#include<fstream>

#include "ColourClass.h"

//unsigned char* ReadBMP(char* filename)
class ReadFromFile
{
private:
	int width, height;

public:
	/* Getters */
	int GetWidth();
	int GetHeight();

	/* Setters */
	void SetWidth(int w);
	void SetHeight(int h);

	/* Methods */
	ColourClass* ReadBMP(char* filename);

};

