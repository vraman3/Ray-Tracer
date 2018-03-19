/**
RayTracing, Transform.cpp
Class to implement the different Transformations.

@author: Vishwanath Raman
@version: 1.0 March/18/2018

*/
#pragma once

#include "Transform.h"
#include "Matrix4x4.h"
#include "CustomMath.h"

/**
	Default constructor
*/
Transform::Transform()
{

}

/**
	Parameterized constructor that takes in a 4x4 array and sets it to
	the transform matrix(m) and also calculates it's inverse(mInv) and stores it.

	@param mat:	The 4x4 double array.
*/
Transform::Transform(double mat[4][4])
{
	m = Matrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	mInv = m.Inverse(m);
}

/**
	Parameterized constructor that takes in a Matrix4x4 and sets it to
	the transform matrix(m) and also calculates it's inverse(mInv) and stores it.

	@param mat:	The Matrix4x4 object.
*/
Transform::Transform(Matrix4x4 &mat): m(mat), mInv(m.Inverse(mat))
{}

/**
	Parameterized constructor that takes in a Matrix4x4 and it's inverse and 
	sets it to the transform matrix(m) and it's inverse(mInv) respectively.

	@param mat:	The Matrix4x4 object.
	@param matInv: The inverse matrix of 'mat'.
*/
Transform::Transform(Matrix4x4 &mat, Matrix4x4 matInv): m(mat), mInv(matInv)
{}

/**
	Getter function to get the current transformation matrix.

	@return	Returns the transformation matrix as a Matrix4x4.
*/
Matrix4x4& Transform::GetMatrix() 
{
	return m;
}

/**
	Getter function to get the inverse of the current transformation matrix.

	@return	Returns the inverse as a Matrix4x4.
*/
Matrix4x4& Transform::GetInverseMatrix()
{ 
	return mInv;
}

/**
	Deprecated. Do not use.
*/
Transform Transform::GetInverse()
{
	return Transform(mInv, m);
}

/**
	Transformation matrix for translation given by VectorClass delta.

	@param delta: The x, y, and z values for translation on the
				  corresponding axes.
	@return Returns the given point after applying the Translation transformation.
*/
Transform Transform::Translate(VectorClass& delta)
{
	Matrix4x4 mT(1, 0, 0, delta.getX(),
				0, 1, 0, delta.getY(),
				0, 0, 1, delta.getZ(),
				0, 0, 0,		1   );

	Matrix4x4 mInvT(1, 0, 0, -delta.getX(),
					0, 1, 0, -delta.getY(),
					0, 0, 1, -delta.getZ(),
					0, 0, 0, 1);

	return Transform(mT, mInvT);
}

/**
	Transformation matrix for scaling given by scale factors x, y, and z.

	@param x: The scale factor for the x axis.
	@param y: The scale factor for the y axis.
	@param z: The scale factor for the z axis.
	@return Returns the given point after applying the Scaling transformation.
*/
Transform Transform::Scale(double x, double y, double z)
{
	Matrix4x4 mS(x, 0, 0, 0,
				 0, y, 0, 0,
				 0, 0, z, 0,
				 0, 0, 0, 1);

	Matrix4x4 mInvS(1/x, 0, 0, 0,
					0, 1/y, 0, 0,
					0, 0, 1/z, 0,
					0, 0, 0, 1);

	return Transform(mS, mInvS);
}

Transform Transform::RotateX(double angle)
{
	double sin_t = sin(Radians(angle));
	double cos_t = cos(Radians(angle));

	Matrix4x4 mRotateX(1, 0, 0, 0,
					   0, cos_t, -sin_t, 0,
					   0, sin_t, cos_t, 0,
					   0, 0, 0, 1);

	return Transform(mRotateX, mRotateX.Transpose(mRotateX));
}

Transform Transform::RotateY(double angle)
{
	return Transform();
}

Transform Transform::RotateZ(double angle)
{
	return Transform();
}

Transform Transform::Rotate(double angle, const VectorClass& axis)
{
	return Transform();
}

Transform Transform::LookAt(const VectorClass& pos, const VectorClass& look, const VectorClass& up)
{
	return Transform();
}

VectorClass Transform::operator()(const VectorClass& point, bool boolPoint)
{
	return VectorClass();
}

VectorClass Transform::operator()(const VectorClass& vec)
{
	return VectorClass();
}



