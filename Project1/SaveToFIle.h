#pragma once

/**
THIS function to write to a 24 bit BMP file was taken from Caleb Piercy's open source Ray Tracer

Code:http://sourceforge.net/projects/rasterrain/
*/
#include<iostream>
#include<fstream>

#include "ColourClass.h"
#include "ToneReproduction.h"

class SaveToFile
{
public:
	SaveToFile();
	void savebmp(const char*, int, int, int, ColourClass*, int);

};

SaveToFile::SaveToFile()
{}

void SaveToFile::savebmp(const char* filename, int w, int h, int dpi, ColourClass* data, int whichTR=0) 
{
	FILE *f;
	int noOfPixels = w*h;
	int s = 4 * noOfPixels;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi*m;

	unsigned char bmpfileheader[14] = { 'B', 'M', 0, 0, 0, 0, 0, 0, 0, 0, 54, 0, 0, 0 };
	unsigned char bmpinfoheader[40] = { 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 24, 0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	f = fopen(filename, "wb");

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	double max = -10000;
	double r, g, b = 0.0;


	for (int i = 0; i < noOfPixels; i++)
	{
		r = data[i].GetRed();
		g = data[i].GetGreen();
		b = data[i].GetBlue();

		max = r;

		if (g > max)
			max = g;
		if (b > max)
			max = b;


		if (max > 1.0)
		{
			data[i].SetRed(data[i].GetRed() / max);
			data[i].SetGreen(data[i].GetGreen() / max);
			data[i].SetBlue(data[i].GetBlue() / max);
		}
	}

	////Do Tone Reproduction here
	ColourClass *display = new ColourClass[noOfPixels];

	ToneReproduction *tp = new ToneReproduction();

	//
	//	Tone Reproduction parameters here
	//
	double Lmax = 10000;
	double Ldmax = 100;

	// For Reinhard
	double a_ForReinhard = 0;
	double	pixelPosORconstValue = 0;
	int setThisChoiceValue = -1;

	// -> CHOOSE WHETHER TO USE A CONSTANT VALUE, VALUE AT A PIXEL, OR DEFAULT IN REINHARD
	// -> "whichTR" must be set to 2 to use Reinhard
	//
	// 0  - Constant Value
	// 1  - Value at a pixel
	// -1 - Default (Use Log Average)
	//
	// Also set pixelPosition or constantValue if either of those are selected in the choice
	//
	//
	setThisChoiceValue = -1;
	pixelPosORconstValue = 0.9;
	a_ForReinhard = 0.18;
	//End of Reinhard parameters
	//
	//

	//For Adaptive Logarithmic
	double biasForAdaptive = 0.85;


	switch (whichTR)
	{
	case 1:display = tp->WardTP(noOfPixels, data, Lmax, Ldmax);															// WARD
		break;

	case 2:display = tp->Reinhard(noOfPixels, data, Lmax, Ldmax, a_ForReinhard, setThisChoiceValue, pixelPosORconstValue);									// REINHARD
		break;

	case 3:display = tp->AdaptiveLogarithmic(noOfPixels, data, Lmax, Ldmax, biasForAdaptive);							// AdaptiveLogarithmic
		break;

	case 0: display = data;
		break;

	default: std::cout << " WRONG INPUT VALUE. NO TONE REPRODUCTION"<<std::endl;
		display = data;
		break;
	}
	

	int testCounter1 = 0;

	// Displaying the RGB value by scaling it to 0 to 255
	for (int i = 0; i < noOfPixels; i++)
	{
		double red = (display[i].GetRed() * 255 );
		double green = (display[i].GetGreen() * 255 );
		double blue = (display[i].GetBlue() * 255);

	/*	double red = (data[i].GetRed() * 255);
		double green = (data[i].GetGreen() * 255);
		double blue = (data[i].GetBlue() * 255);*/
		
		unsigned char color[3] = { (int)floor(blue), (int)floor(green), (int)floor(red) };

		fwrite(color, 1, 3, f);
	}

	fclose(f);
}