/**
	RayTracing, ColourClass.cpp
	Class to implement storage of Colour value for a pixel.

	@author: Vishwanath Raman
	@version: 1.0 Oct/12/2017

*/
#include "ColourClass.h"

/**
	Default Constructor.
*/
ColourClass::ColourClass()
{
	red = 0.0;
	green = 0.0;
	blue = 0.0;
}
/**
	Parameterized Constructor.
*/
ColourClass::ColourClass(double paramRed, double paramGreen, double paramBlue)
{
	red = paramRed;
	green = paramGreen;
	blue = paramBlue;
}

/**
	Get the red hue value for current pixel.

	@return the value of the red hue value.
*/
double ColourClass::GetRed() { return red; }

/**
	Get the green hue value for current pixel.

	@return the value of the green hue value.
*/
double ColourClass::GetGreen() { return green; }

/**
	Get the blue hue value for current pixel.

	@return the value of the blue hue value.
*/
double ColourClass::GetBlue() { return blue; }

/**
	Set the red hue value for current pixel.

	@param paramVal: the value of the red hue to be set for current pixel.
*/
void ColourClass::SetRed(double paramVal) { red = paramVal; }

/**
	Set the green hue value for current pixel.

	@param paramVal: the value of the green hue to be set for current pixel.
*/
void ColourClass::SetGreen(double paramVal) { green = paramVal; }

/**
	Set the blue hue value for current pixel.

	@param paramVal: the value of the blue hue to be set for current pixel.
*/
void ColourClass::SetBlue(double paramVal) { blue = paramVal; }

/**
	Operator overload for multiplying (*) a ColourClass with a constant.
	
	@param b: The ColourClass to be multiplied with the first.
	@return the multiplication of both ColourClass, as a VectorClass.
*/
ColourClass ColourClass::operator*(const double b) const
{
	return ColourClass(this->red * b, this->green * b, this->blue * b);
}

ColourClass ColourClass::operator/(const double b) const
{
	return ColourClass(this->red / b, this->green / b, this->blue / b);
}

ColourClass ColourClass::operator+(const double b) const
{
	return ColourClass(this->red + b, this->green + b, this->blue + b);
}

ColourClass ColourClass::operator-(const double b) const
{
	return ColourClass(this->red - b, this->green - b, this->blue - b);
}
ColourClass ColourClass::operator*(const ColourClass& b) const
{
	return ColourClass(this->red * b.red, this->green * b.green, this->blue * b.blue);
}

ColourClass ColourClass::operator+(const ColourClass& b) const
{
	return ColourClass(this->red + b.red, this->green + b.green, this->blue + b.blue);
}

ColourClass ColourClass::operator-(const ColourClass& b) const
{
	return ColourClass(this->red - b.red, this->green - b.green, this->blue - b.blue);
}

void ColourClass::resetColour()
{
	this->red = 0.0;
	this->green = 0.0;
	this->blue = 0.0;
}