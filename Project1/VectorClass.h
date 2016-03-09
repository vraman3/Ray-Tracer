#pragma once

//Author: Vishwanath Raman
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

double VectorClass::operator[](const int dimension) const
{
	switch (dimension)
	{
		case 0: return x;
				break;

		case 1: return y;
				break;

		case 2: return z;
				break;

		default: return NULL;
				break;
	}
}

VectorClass VectorClass::operator+(const VectorClass& b) const
{
	return VectorClass(this->x + b.x, this->y + b.y, this->z + b.z);
}

VectorClass VectorClass::operator-(const VectorClass& b) const
{
	return VectorClass(this->x - b.x, this->y - b.y, this->z - b.z);
}

VectorClass VectorClass::operator*(const VectorClass& b) const
{
	return VectorClass(this->x * b.x, this->y * b.y, this->z * b.z);
}

VectorClass VectorClass::operator*(const double b) const
{
	return VectorClass(this->x * b, this->y * b, this->z * b);
}

VectorClass VectorClass::operator/(const double b) const
{
	return VectorClass(this->x / b, this->y / b, this->z / b);
}

VectorClass::VectorClass()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

VectorClass::VectorClass(double i, double j, double k)
{
	x = i;
	y = j;
	z = k;
}

double VectorClass::GetX()
{
	return x;
}

double VectorClass::GetY()
{
	return y;
}

double VectorClass::GetZ()
{
	return z;
}

void VectorClass::SetX(double val)
{
	x = val;
}

void VectorClass::SetY(double val)
{
	y = val;
}

void VectorClass::SetZ(double val)
{
	z = val;
}


double VectorClass::Magnitude()
{
	double temp = x*x + y*y + z*z;
	return sqrt(temp);
	
}
double VectorClass::DotProd(VectorClass temp)
{
	return x * temp.GetX() + y * temp.GetY() + z * temp.GetZ();
}

VectorClass VectorClass::CrossProd(VectorClass temp)
{
	return VectorClass(y*temp.GetZ() - z*temp.GetY(), z*temp.GetX() - x*temp.GetZ(), x*temp.GetY() - y*temp.GetX());
}

VectorClass VectorClass::Normalize()
{
	double value = sqrt(x*x + y*y + z*z);
	return VectorClass(x / value, y / value, z / value);
}