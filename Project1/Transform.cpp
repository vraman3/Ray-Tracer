/**
RayTracing, Transform.cpp
Class to implement the different Transformations.

@author: Vishwanath Raman
@version: 1.0 March/18/2018

*/
#pragma once

#include "Transform.h"
#include "Matrix4x4.h"

Transform::Transform()
{

}

Transform::Transform(double mat[4][4])
{
	m = Matrix4x4(mat[0][0], mat[0][1], mat[0][2], mat[0][3],
		mat[1][0], mat[1][1], mat[1][2], mat[1][3],
		mat[2][0], mat[2][1], mat[2][2], mat[2][3],
		mat[3][0], mat[3][1], mat[3][2], mat[3][3]);
	mInv = m.Inverse(m);
}

Transform::Transform(const Matrix4x4 &mat): m(mat), mInv(m.Inverse(mat))
{

}

Transform::Transform(const Matrix4x4 &mat, const Matrix4x4 matInv)
{

}

Transform Transform::GetInverse() const
{

}

Transform Transform::Translate(const VectorClass delta)
{
	return Transform();
}

Transform Transform::Scale(double x, double y, double z)
{
	return Transform();
}

Transform Transform::RotateX(double angle)
{
	return Transform();
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



