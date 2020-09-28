/**
	RayTracing, ColourClass.h
	Header file for the ColourClass class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/12/2017

*/
#pragma once

#include <iostream>

class ColourClass
{
private:
	double red, green, blue;

public:
	/* Constructors */
	ColourClass();
	ColourClass(double, double, double);

	/* Getters */
	double GetRed();
	double GetGreen();
	double GetBlue();

	/* Setters */
	void SetRed(double);
	void SetGreen(double);
	void SetBlue(double);

	/* Opeator Overloading*/
	ColourClass operator*(const double) const;
	ColourClass operator/(const double) const;
	ColourClass operator+(const double) const;
	ColourClass operator-(const double) const;
	ColourClass operator*(const ColourClass&) const;
	ColourClass operator+(const ColourClass&) const;
	ColourClass operator-(const ColourClass&) const;
	friend std::ostream& operator<<(std::ostream& os, ColourClass& color);

	/* Methods */
	void resetColour();
};

