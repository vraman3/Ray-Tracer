/**
RayTracing, Transform.h
Header file for the Transform class.

@author: Vishwanath Raman
@version: 1.0 March/18/2018

*/
#pragma once

#include "Matrix4x4.h"
class Transform
{
private:
	/* Variables */
	Matrix4x4 m, mInv;

public:
	/* Constructors */
	Transform();
	Transform(float mat[4][4]);
	Transform(const Matrix4x4 &mat);
};