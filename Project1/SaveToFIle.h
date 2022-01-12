#pragma once

/**
THIS function to write to a 24 bit BMP file was taken from Caleb Piercy's open source Ray Tracer

Code:http://sourceforge.net/projects/rasterrain/
*/
#include<iostream>
#include<fstream>

#include "ColourClass.h"
#include "ToneReproduction.h"
#include "KDNode.h"

class SaveToFIle
{
public:
	SaveToFIle();
	void saveRawObjectRGBData(const char* filename, int imageWidth, int imageHeight, ColourClass* pixels);
	void savebmp(const char*, int, int, int, ColourClass*, int);
	void saveppm(const char* filename, int imageWidth, int imageHeight, ColourClass* pixels);
	void savetxtkdtree(KDNode kdtree);
};

