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
	Operator overloading for multiplying (*) a ColourClass with a constant.
	
	@param b: The constant to be multiplied with the ColourClass.
	@return the VectorClass after multiplication of each of its elements 
			with the constant
*/
ColourClass ColourClass::operator*(const double b) const
{
	return ColourClass(this->red * b, this->green * b, this->blue * b);
}

/**
	Operator overloading for dividing (/) a ColourClass with a constant.
	
	@param b: The divisor.
	@return the division of each of the elements of ColourClass with the divisor.
*/
ColourClass ColourClass::operator/(const double b) const
{
	return ColourClass(this->red / b, this->green / b, this->blue / b);
}

/**
	Operator overloading for adding a ColourClass with a constant.
	Add the constant to each element of the ColourClass.

	@param b: The constant to be added.
	@return the addition of the ColourClass with the constant.
*/
ColourClass ColourClass::operator+(const double b) const
{
	return ColourClass(this->red + b, this->green + b, this->blue + b);
}

/**
	Operator overloading for subtracting a constant from a ColourClass.
	Subtract the constant from each element of the ColourClass.

	@param b: The constant to be added.
	@return the ColourClass after  the subtraction.
*/
ColourClass ColourClass::operator-(const double b) const
{
	return ColourClass(this->red - b, this->green - b, this->blue - b);
}

/**
	Operator overloading for multiplying two ColourClasses together.

	@param b: The ColourClass to be multiplied to the first.
	@return the addition of both the ColourClasses.
*/
ColourClass ColourClass::operator*(const ColourClass& b) const
{
	return ColourClass(this->red * b.red, this->green * b.green, this->blue * b.blue);
}

/**
	Operator overloading to add two ColourClasses together.

	@param b: The ColourClass to be added to the first.
	@return the addition of both the ColourClasses.
*/
ColourClass ColourClass::operator+(const ColourClass& b) const
{
	return ColourClass(this->red + b.red, this->green + b.green, this->blue + b.blue);
}

/**
	Operator overloading to subtract a ColourClasses from the current ColourClass.

	@param b: The ColourClass to be subtracted from the first.
	@return the resultant ColourClass after the subtraction.
*/
ColourClass ColourClass::operator-(const ColourClass& b) const
{
	return ColourClass(this->red - b.red, this->green - b.green, this->blue - b.blue);
}

/**
	Reset the colour of the current pixel to Black (R,G,B = 0,0,0)
*/
void ColourClass::resetColour()
{
	this->red = 0.0;
	this->green = 0.0;
	this->blue = 0.0;
}

	std::ostream & operator<<(std::ostream & os, ColourClass & colour)
	{
		os << "R: " << colour.GetRed() << " G: " << colour.GetGreen() << " B: " << colour.GetBlue() << std::endl;

		return os;
	}
