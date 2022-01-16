/**
	RayTracing, ColourClass.h
	Header file for the ColourClass class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/12/2017

*/
#pragma once

#include <iostream>
#include "VectorClass.h"

class ColourClass
{
private:
	double red, green, blue;

public:
	/* Constructors */
	ColourClass();
	ColourClass(double red, double green, double blue);
	ColourClass(VectorClass vector);

	/* Getters */
	double GetRed();
	double GetGreen();
	double GetBlue();

	/* Setters */
	void SetRed(double red);
	void SetGreen(double green);
	void SetBlue(double blue);

	/* Opeator Overloading*/
	ColourClass operator*(const double) const;
	ColourClass operator/(const double) const;
	ColourClass operator+(const double) const;
	ColourClass operator-(const double) const;
	ColourClass operator*(const ColourClass&) const;
	ColourClass operator+(const ColourClass&) const;
	ColourClass operator-(const ColourClass&) const;
	bool operator==(const ColourClass&) const;
	friend std::ostream& operator<<(std::ostream& os, ColourClass& color);

	/* Methods */
	void resetColour();
};

