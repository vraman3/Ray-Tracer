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
	VectorClass();
	VectorClass(double, double, double);
	//VectorClass(MatrixClass);
	double GetX();
	double GetY();
	double GetZ();

	void SetX(double);
	void SetY(double);
	void SetZ(double);

	VectorClass operator+(const VectorClass&) const;
	VectorClass operator-(const VectorClass&) const;
	VectorClass operator*(const VectorClass&) const;
	VectorClass operator*(const double) const;
	VectorClass operator/(const double) const;
	
	double operator[](const int) const;

	double Magnitude();
	double DotProd(VectorClass );
	VectorClass CrossProd(VectorClass );
	VectorClass Normalize();

};

//VectorClass::VectorClass(MatrixClass m) : x(m[0][0] / m[3][0]), y(m[1][0] / m[3][0]), z(m[2][0] / m[3][0])
//{}

