#include "ColourClass.h"

ColourClass::ColourClass()
{
	red = 0.0;
	green = 0.0;
	blue = 0.0;
}

ColourClass::ColourClass(double r, double g, double b)
{
	red = r;
	green = g;
	blue = b;
}

double ColourClass::GetRed() { return red; }

double ColourClass::GetGreen() { return green; }

double ColourClass::GetBlue() { return blue; }

void ColourClass::SetRed(double val) { red = val; }

void ColourClass::SetGreen(double val) { green = val; }

void ColourClass::SetBlue(double val) { blue = val; }

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