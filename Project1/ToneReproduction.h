#pragma once

//Author: Vishwanath Raman
#include "ColourClass.h"
#include "SaveToFIle.h"

class ToneReproduction
{
public:

	ToneReproduction(){}

	ColourClass* WardTP(int, ColourClass*, double, double);
	ColourClass* Reinhard(int, ColourClass *, double, double, double, int, double);
	ColourClass* AdaptiveLogarithmic(int, ColourClass *, double, double, double);
};

ColourClass* ToneReproduction::AdaptiveLogarithmic(int noOfPixels, ColourClass *data, double Lmax, double Ldmax, double b)
{
	ColourClass *scaledToLmax = new ColourClass[noOfPixels];

	// Scale all values to 0 to Lmax
	for (int i = 0; i < noOfPixels; i++)
	{
		scaledToLmax[i].SetRed(data[i].GetRed() * Lmax);
		scaledToLmax[i].SetGreen(data[i].GetGreen() * Lmax);
		scaledToLmax[i].SetBlue(data[i].GetBlue() * Lmax);
	}

	double *Lw = new double[noOfPixels];

	// Get Lw for each RGB value			Get Pixel Luminance
	for (int i = 0; i < noOfPixels; i++)
	{
		Lw[i] = 0.27 * scaledToLmax[i].GetRed()
			+ 0.67 * scaledToLmax[i].GetGreen()
			+ 0.06 * scaledToLmax[i].GetBlue();
	}

	// Get LogAverage luminance for the scene
	double LogAverage = 0;
	double temp = 0;

	// Summation term
	for (int i = 0; i < noOfPixels; i++)
	{
		temp += log(0.00001 + Lw[i]);
	}

	LogAverage = exp(temp / noOfPixels);


	/////////////////// 2nd type	/////////////////////				
	//double firstTerm = (Ldmax * 0.01) / log10(Lmax + 1);

	//ColourClass* target = new ColourClass[noOfPixels];

	//for (int i = 0; i < noOfPixels; i++)
	//{
	//	double biasFactor = pow((Lw[i] / Lmax), (log(b) / log(0.5)));

	//	double secondTerm = log(Lw[i] + 1) / log(2 + biasFactor * 8);

	//	double scaleFactor = firstTerm * secondTerm;

	//	target[i].SetRed(scaledToLmax[i].GetRed() * scaleFactor);
	//	target[i].SetBlue(scaledToLmax[i].GetBlue() * scaleFactor);
	//	target[i].SetGreen(scaledToLmax[i].GetGreen() * scaleFactor);
	//}

	Lmax = Lmax / LogAverage;

	/////////////////// 3rd type	/////////////////////
	double firstTerm = (Ldmax * 0.01) / log10(Lmax + 1);

	ColourClass* target = new ColourClass[noOfPixels];

	for (int i = 0; i < noOfPixels; i++)
	{
		double biasFactor = pow((Lw[i] / (Lmax * LogAverage)), (log(b) / log(0.5)));

		double secondTerm = log((Lw[i] / LogAverage) + 1) / log(2 + biasFactor * 8);

		double scaleFactor = firstTerm * secondTerm;

		target[i].SetRed(scaledToLmax[i].GetRed() * scaleFactor);
		target[i].SetGreen(scaledToLmax[i].GetGreen() * scaleFactor);
		target[i].SetBlue(scaledToLmax[i].GetBlue() * scaleFactor);
	}

	double max = -10000;
	double red, green, blue = 0.0;
	int testCounter = 0;

	for (int i = 0; i < noOfPixels; i++)
	{
		red = target[i].GetRed();
		green = target[i].GetGreen();
		blue = target[i].GetBlue();

		max = red;
		if (green > max)
			max = green;
		if (blue > max)
			max = blue;

		if (max > 1.0)
		{
			target[i].SetRed(target[i].GetRed() / max);
			target[i].SetGreen(target[i].GetGreen() / max);
			target[i].SetBlue(target[i].GetBlue() / max);
		}
	}

	return target;
}


ColourClass* ToneReproduction::Reinhard(int noOfPixels, ColourClass *data, double Lmax, double Ldmax, double a, int choice, double incomingValue)
{
	ColourClass *scaledToLmax = new ColourClass[noOfPixels];

	// Scale all values to 0 to Lmax
	for (int i = 0; i < noOfPixels; i++)
	{
		scaledToLmax[i].SetRed(data[i].GetRed() * Lmax);
		scaledToLmax[i].SetGreen(data[i].GetGreen() * Lmax);
		scaledToLmax[i].SetBlue(data[i].GetBlue() * Lmax);
	}

	double *Lw = new double[noOfPixels];

	// Get Lw for each RGB value			Get Pixel Luminance
	for (int i = 0; i < noOfPixels; i++)
	{
		Lw[i] = 0.27 * scaledToLmax[i].GetRed()
			+ 0.67 * scaledToLmax[i].GetGreen()
			+ 0.06 * scaledToLmax[i].GetBlue();
	}

	// Get LogAverage luminance for the scene
	double LogAverage = 0;
	double temp = 0;

	// Summation term
	for (int i = 0; i < noOfPixels; i++)
	{
		temp += log(0.00001 + Lw[i]);
	}

	if (choice == -1)
	{
		LogAverage = exp(temp / noOfPixels);
	}
	else if (choice == 0)
	{
		LogAverage = incomingValue;
	}
	else if (choice == 1)
	{
		if (incomingValue > noOfPixels || incomingValue < 0)
		{
			std::cout << " Index cannot exceed number of pixels or be negative. \n Defaulting to Log Average Luminance" << std::endl;
			LogAverage = exp(temp / noOfPixels);
		}
		else
			LogAverage = Lw[(int)incomingValue];
	}

	
	//a = 0.18;
	//LogAverage = 9;
	std::cout << LogAverage << " ";

	ColourClass* scaledRGB = new ColourClass[noOfPixels];

	for (int i = 0; i < noOfPixels; i++)
	{
		scaledRGB[i].SetRed(scaledToLmax[i].GetRed() * (a / LogAverage));
		scaledRGB[i].SetGreen(scaledToLmax[i].GetGreen() * (a / LogAverage));
		scaledRGB[i].SetBlue(scaledToLmax[i].GetBlue() * (a / LogAverage));
	}

	//Find reflectance
	ColourClass* reflectanceRGB = new ColourClass[noOfPixels];

	for (int i = 0; i < noOfPixels; i++)
	{
		double r = scaledRGB[i].GetRed();
		double g = scaledRGB[i].GetGreen();
		double b = scaledRGB[i].GetBlue();

		reflectanceRGB[i].SetRed(r / (1 + r));
		reflectanceRGB[i].SetGreen(g / (1 + g));
		reflectanceRGB[i].SetBlue(b / (1 + b));
	}

	ColourClass* target = new ColourClass[noOfPixels];

	for (int i = 0; i < noOfPixels; i++)
	{
		double r = reflectanceRGB[i].GetRed();
		double g = reflectanceRGB[i].GetGreen();
		double b = reflectanceRGB[i].GetBlue();

		target[i].SetRed(r * Ldmax);
		target[i].SetGreen(g * Ldmax);
		target[i].SetBlue(b * Ldmax);
	}

	double max = -10000;
	double r, g, b = 0.0;
	int testCounter = 0;

	for (int i = 0; i < noOfPixels; i++)
	{
		r = target[i].GetRed();
		g = target[i].GetGreen();
		b = target[i].GetBlue();

		max = r;
		if (g > max)
			max = g;
		if (b > max)
			max = b;

		if (max > 1.0)
		{
			target[i].SetRed(target[i].GetRed() / max);
			target[i].SetGreen(target[i].GetGreen() / max);
			target[i].SetBlue(target[i].GetBlue() / max);
		}
	}

	return target;
}

ColourClass* ToneReproduction::WardTP(int noOfPixels, ColourClass *data, double Lmax, double Ldmax)
{
	int testCounter = 0, k = noOfPixels;

	ColourClass *scaledToLmax = new ColourClass[noOfPixels];

	// Scale all values to 0 to Lmax
	for (int i = 0; i < k; i++)
	{
		scaledToLmax[i].SetRed(data[i].GetRed() * Lmax);
		scaledToLmax[i].SetGreen(data[i].GetGreen() * Lmax);
		scaledToLmax[i].SetBlue(data[i].GetBlue() * Lmax);
	}

	double *Lw = new double[noOfPixels];

	// Get Lw for each RGB value			Get Pixel Luminance
	for (int i = 0; i < k; i++)
	{
		Lw[i] = 0.27 * scaledToLmax[i].GetRed()
			+ 0.67 * scaledToLmax[i].GetGreen()
			+ 0.06 * scaledToLmax[i].GetBlue();
	}

	// Get LogAverage luminance for the scene
	double LogAverage = 0;
	double temp = 0;

	// Summation term
	for (int i = 0; i < k; i++)
	{
		temp += log(0.00001 + Lw[i]);
	}

	LogAverage = exp(temp / noOfPixels);

	double num = 1.219 + pow((Ldmax / 2), 0.4);					//Numerator

	double denom = 1.219 + pow(LogAverage, 0.4);				//Denominator

	double sf = pow((num / denom), 2.5);						// sf

	ColourClass *display = new ColourClass[noOfPixels];

	double scaleFactor = sf / Ldmax;

	//Multiply by scale factor = sf*Lw[i]
	for (int i = 0; i < k; i++)
	{
		display[i].SetRed(scaledToLmax[i].GetRed() * scaleFactor);
		display[i].SetGreen(scaledToLmax[i].GetGreen() * scaleFactor);
		display[i].SetBlue(scaledToLmax[i].GetBlue() * scaleFactor);
	}

	double max2 = -10000;
	double r2, g2, b2 = 0.0;

	for (int i = 0; i < k; i++)
	{
		r2 = display[i].GetRed();
		g2 = display[i].GetGreen();
		b2 = display[i].GetBlue();

		max2 = r2;

		if (g2 > max2)
			max2 = g2;
		if (b2 > max2)
			max2 = b2;

		if (max2 > 1.0)
		{
			display[i].SetRed(display[i].GetRed() / max2);
			display[i].SetGreen(display[i].GetGreen() / max2);
			display[i].SetBlue(display[i].GetBlue() / max2);
		}
	}
	return display;
}