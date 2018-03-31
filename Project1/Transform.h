/**
RayTracing, Transform.h
Header file for the Transform class.

@author: Vishwanath Raman
@version: 1.0 March/18/2018

*/
#pragma once


#include "Matrix4x4.h"
#include "VectorClass.h"
#include "RayClass.h"
#include "AABBClass.h"


class Transform
{
	
private:
	/* Variables */
	Matrix4x4 m4x4, mInv;
		
public:
	/* Constructors */
	Transform();
	Transform(double paramMatArray[4][4]);
	Transform(Matrix4x4 &paramMat);
	Transform(Matrix4x4 &paramMat, Matrix4x4 paramMatInv);

	/* Getters */
	Matrix4x4 &GetMatrix();
	Matrix4x4 &GetInverseMatrix();

	Transform GetInverse();

	/* Transformations */
	Transform Translate(VectorClass& delta);
	Transform Scale(double x, double y, double z);

	/* Rotations */
	Transform RotateX(double angle);
	Transform RotateY(double angle);
	Transform RotateZ(double angle);

	Transform Rotate(double angle, VectorClass& axis);

	Transform LookAt(VectorClass& pos, VectorClass& look, VectorClass& up);

	/*
		Operator overloading, to transform points, normals, vectors and rays
		and axis-aligned bounding boxes
	*/

	/*	Points	*/
	VectorClass operator()(VectorClass& point, int intPoint);
	void operator()(VectorClass& point, VectorClass* pOut, int intPoint);

	/*	Vectors	*/
	VectorClass operator()(VectorClass& vec);
	void operator()(VectorClass& vec, VectorClass* vecOut);

	/*	Normals	*/
	VectorClass operator()(VectorClass& normal, float fNormal);
	void operator()(VectorClass& normal, VectorClass* normalOut, float fNormal);

	// Rays
	RayClass operator()(RayClass& ray);
	void operator()(RayClass& ray, RayClass* rayOut);

	// Axis-Aligned Bounding Box
	AABBClass operator()(AABBClass& box);

	// Multiply two Transforms. Calling Transform post multiplied by t2.
	Transform operator*(Transform &t2);
};