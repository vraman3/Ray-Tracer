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
	Transform(Matrix4x4 &mat);
	Transform(Matrix4x4 &mat, Matrix4x4 matInv);

	Matrix4x4 &GetMatrix() { return m; }
	Matrix4x4 &GetInverseMatrix(){ return mInv; }

	Transform GetInverse();
	Transform Translate(VectorClass& delta);
	Transform Scale(double x, double y, double z);

	Transform RotateX(double angle);
	Transform RotateY(double angle);
	Transform RotateZ(double angle);

	Transform Rotate(double angle, VectorClass& axis);

	Transform LookAt(VectorClass& pos, VectorClass& look, VectorClass& up);

	VectorClass operator()(VectorClass& point, bool boolPoint);
	VectorClass operator()(VectorClass& vec);
};