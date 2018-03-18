/**
RayTracing, Matrix4x4.cpp
Class to implement 4x4 Matrices

@author: Vishwanath Raman
@version: 1.0 March/17/2018

*/
#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
	for (int i = 0; i < 4; ++i)
		for (int j = 0; j < 4; ++j)
		{
			if (i == j)
				m[i][j] = 1.;
			else
				m[i][j] = 0.;
		}
}

Matrix4x4::Matrix4x4(float mat[4][4])
{
	memcpy(m, mat, 16 * sizeof(float));
}

Matrix4x4::Matrix4x4(double t00, double t01, double t02, double t03, double t10, double t11, double t12, double t13,
					double t20, double t21, double t22, double t23, double t30, double t31, double t32, double t33)
{
	m[0][0] = t00;	m[0][1] = t01;	m[0][2] = t02;	m[0][3] = t03;
	m[1][0] = t10;	m[1][1] = t11;	m[1][2] = t12;	m[1][3] = t13;
	m[2][0] = t20;	m[2][1] = t21;	m[2][2] = t22;	m[2][3] = t23;
	m[3][0] = t30;	m[3][1] = t31;	m[3][2] = t32;	m[3][3] = t33;
}

Matrix4x4* Matrix4x4::Tranpose()
{
	return new Matrix4x4(
		m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]);
}