/**
RayTracing, VectorClass.h
Custom class for direction vector

@author: Vishwanath Raman
@version: 1.0 Oct/07/2017

*/

#pragma once

#include <math.h>
//#include "MatrixClass.h"

class VectorClass
{
private:
	double x, y, z;

public:
	// Constructors
	VectorClass();
	VectorClass(double, double, double);
	//VectorClass(MatrixClass);

	// Getters
	double GetX();
	double GetY();
	double GetZ();

	// Setters
	void SetX(double);
	void SetY(double);
	void SetZ(double);

	// Overloaded operators
	VectorClass operator+(const VectorClass&) const;
	VectorClass operator-(const VectorClass&) const;
	VectorClass operator*(const VectorClass&) const;
	VectorClass operator*(const double) const;
	VectorClass operator/(const double) const;
	double operator[](const int) const;

	// Methods
	double Magnitude();
	double DotProd(VectorClass );
	VectorClass CrossProd(VectorClass );
	VectorClass Normalize();

};

