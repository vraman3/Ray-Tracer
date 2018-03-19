/**
RayTracing, Matrix4x4.cpp
Class to implement 4x4 Matrices

@author: Vishwanath Raman
@version: 1.0 March/17/2018

*/
#include "Matrix4x4.h"

/**
	Default constructor. Identity matrix. Row-major format.
*/
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

/**
	Parameterized constructor to take a 4x4 array as input.
	The resultant Matrix4x4 wil be row-major.

	@param	mat: 4x4 array to be assigned to new Matrix4x4 object.
*/
Matrix4x4::Matrix4x4(double mat[4][4])
{
	memcpy(m, mat, 16 * sizeof(double));
}

/**
	Parameterized constructor to take in 16 double values. Resultant Matrix4x4
	will be in Row-major format.

	@param	t00-t33: Individual values to be assigned to corresponding elements
					 of the matrix. t00 refers to row 0 and column 0,
					 t01 refers to row 0 and column 1, and so on.
*/
Matrix4x4::Matrix4x4(double t00, double t01, double t02, double t03, double t10, double t11, double t12, double t13,
					double t20, double t21, double t22, double t23, double t30, double t31, double t32, double t33)
{
	m[0][0] = t00;	m[0][1] = t01;	m[0][2] = t02;	m[0][3] = t03;
	m[1][0] = t10;	m[1][1] = t11;	m[1][2] = t12;	m[1][3] = t13;
	m[2][0] = t20;	m[2][1] = t21;	m[2][2] = t22;	m[2][3] = t23;
	m[3][0] = t30;	m[3][1] = t31;	m[3][2] = t32;	m[3][3] = t33;
}

/**
	Return the transpose of a given Matrix. Resultant Matrix4x4 will be in
	row-major format.

	@param	mat: The Matrix4x4 object to be transposed.
	@return The transposed version of the give Matrix4x4 object, i.e. mat)
*/
Matrix4x4 Matrix4x4::Transpose(const Matrix4x4& mat)
{
	return Matrix4x4(
		mat.m[0][0], mat.m[1][0], mat.m[2][0], mat.m[3][0],
		mat.m[0][1], mat.m[1][1], mat.m[2][1], mat.m[3][1],
		mat.m[0][2], mat.m[1][2], mat.m[2][2], mat.m[3][2],
		mat.m[0][3], mat.m[1][3], mat.m[2][3], mat.m[3][3]);
}

/**
	Return the result of multiplication of two matrices.
	(m1 is post-multiplied with m2) Resultant Matrix4x4 in row-major format.
*/
Matrix4x4 Matrix4x4::Mul(const Matrix4x4& m1, const Matrix4x4& m2)
{
	Matrix4x4 result;

	for(int i=0; i<4; i++)
		for (int j = 0; j < 4; j++)
		{
			//								inner product of 	
			// (i,j)th element of result =  i-th row of m1 multiplied by
			//								j-th row of m2.
			result.m[i][j] =	m1.m[i][0] * m2.m[0][j] +
								m1.m[i][1] * m2.m[1][j] +
								m1.m[i][2] * m2.m[2][j] +
								m1.m[i][3] * m2.m[3][j];
		}

	return result;
}