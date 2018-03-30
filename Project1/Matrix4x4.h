/**
RayTracing, Matrix4x4.h
Header file for the Matrix Class.

@author: Vishwanath Raman
@version: 1.0 March/17/2018

*/
#pragma once

#include <iostream>
#include "Reference.h"

class Matrix4x4
{
	

public:
	double m[4][4];
	/* Constructors */
	Matrix4x4();
	Matrix4x4(double matArray[4][4]);
	Matrix4x4(	double t00, double t01, double t02, double t03, double t10, double t11, double t12, double t13,
				double t20, double t21, double t22, double t23, double t30, double t31, double t32, double t33);

	/* Functions */
	Matrix4x4 Transpose();
	Matrix4x4 Mul( Matrix4x4& m2);
	Matrix4x4 Inverse();
};