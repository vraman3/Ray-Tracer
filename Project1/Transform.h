/**
RayTracing, Transform.h
Header file for the Transform class.

@author: Vishwanath Raman
@version: 1.0 March/18/2018

*/
#pragma once

#include "Matrix4x4.h"
#include "VectorClass.h"

class Transform
{
private:
	/* Variables */
	Matrix4x4 m, mInv;
	
public:
	/* Constructors */
	Transform();
	Transform(double mat[4][4]);
	Transform(const Matrix4x4 &mat);
	Transform(const Matrix4x4 &mat, const Matrix4x4 matInv);

	Transform GetInverse() const;
	Transform Translate(const VectorClass delta);
	Transform Scale(double x, double y, double z);

	Transform RotateX(double angle);
	Transform RotateY(double angle);
	Transform RotateZ(double angle);

	Transform Rotate(double angle, const VectorClass& axis);

	Transform LookAt(const VectorClass& pos, const VectorClass& look, const VectorClass& up);

	VectorClass operator()(const VectorClass& point, bool boolPoint);
	VectorClass operator()(const VectorClass& vec);
};