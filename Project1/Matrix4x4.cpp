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
				matArray[i][j] = 1.;
			else
				matArray[i][j] = 0.;
		}
}

/**
	Parameterized constructor to take a 4x4 array as input.
	The resultant Matrix4x4 wil be row-major.

	@param	paramMatArray: 4x4 array to be assigned to new Matrix4x4 object.
*/
Matrix4x4::Matrix4x4(double paramMatArray[4][4])
{
	memcpy(matArray, paramMatArray, 16 * sizeof(double));
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
	matArray[0][0] = t00;	matArray[0][1] = t01;	matArray[0][2] = t02;	matArray[0][3] = t03;
	matArray[1][0] = t10;	matArray[1][1] = t11;	matArray[1][2] = t12;	matArray[1][3] = t13;
	matArray[2][0] = t20;	matArray[2][1] = t21;	matArray[2][2] = t22;	matArray[2][3] = t23;
	matArray[3][0] = t30;	matArray[3][1] = t31;	matArray[3][2] = t32;	matArray[3][3] = t33;
}

std::ostream& operator<<(std::ostream & os,const Matrix4x4& displayMat)
{
	os << displayMat.matArray[0][0] << " " << displayMat.matArray[0][1] << " " << displayMat.matArray[0][2] << " " << displayMat.matArray[0][3] << std::endl;
	os << displayMat.matArray[1][0] << " " << displayMat.matArray[1][1] << " " << displayMat.matArray[1][2] << " " << displayMat.matArray[1][3] << std::endl;
	os << displayMat.matArray[2][0] << " " << displayMat.matArray[2][1] << " " << displayMat.matArray[2][2] << " " << displayMat.matArray[2][3] << std::endl;
	os << displayMat.matArray[3][0] << " " << displayMat.matArray[3][1] << " " << displayMat.matArray[3][2] << " " << displayMat.matArray[3][3] << std::endl;

	return os;
}

/**
	Return the transpose of a current Matrix4x4. Resultant Matrix4x4 will be in
	row-major format.

	@return The transposed version of the calling Matrix4x4 object, i.e. m4x4)
*/
Matrix4x4 Matrix4x4::Transpose()
{
	return Matrix4x4(
		matArray[0][0], matArray[1][0], matArray[2][0], matArray[3][0],
		matArray[0][1], matArray[1][1], matArray[2][1], matArray[3][1],
		matArray[0][2], matArray[1][2], matArray[2][2], matArray[3][2],
		matArray[0][3], matArray[1][3], matArray[2][3], matArray[3][3]);
}

/**
	Return the result of multiplication of two matrices.
	m1 is the calling Matrix4x4, and m2 is the passed Matrix4x4 argument.
	(m1 is post-multiplied with m2, i.e. m1*m2) Resultant Matrix4x4 in row-major format.
*/
Matrix4x4 Matrix4x4::Mul( Matrix4x4& m2)
{
	Matrix4x4 result;

	for(int i=0; i<4; i++)
		for (int j = 0; j < 4; j++)
		{
			//								inner product of 	
			// (i,j)th element of result =  i-th row of m1 multiplied by
			//								j-th row of m2.
			result.matArray[i][j] =	matArray[i][0] * m2.matArray[0][j] +
								matArray[i][1] * m2.matArray[1][j] +
								matArray[i][2] * m2.matArray[2][j] +
								matArray[i][3] * m2.matArray[3][j];
		}

	return result;
}

/**
	Calculate Inverse of a given Matrix4x4. 
	Currently taken from PBRT Book by Matt Pharr and Greg Humphreys!
	
	@return The inverse 4x4 Matrix of the given input Matrix.
*/
Matrix4x4 Matrix4x4::Inverse()
{
	int indxc[4], indxr[4];
	int ipiv[4] = { 0, 0, 0, 0 };
	double minv[4][4];
	memcpy(minv, matArray, 4 * 4 * sizeof(double));
	for (int i = 0; i < 4; i++) {
		int irow = -1, icol = -1;
		float big = 0.;
		// Choose pivot
		for (int j = 0; j < 4; j++) {
			if (ipiv[j] != 1) {
				for (int k = 0; k < 4; k++) {
					if (ipiv[k] == 0) {
						if (fabs(minv[j][k]) >= big) {
							big = double(fabs(minv[j][k]));
							irow = j;
							icol = k;
						}
					}
					else if (ipiv[k] > 1)
						std::cout << "Error. Singular matrix in MatrixInvert" << std::endl;//Error("Singular matrix in MatrixInvert");
				}
			}
		}
		++ipiv[icol];
		// Swap rows _irow_ and _icol_ for pivot
		if (irow != icol) {
			for (int k = 0; k < 4; ++k)
				std::swap(minv[irow][k], minv[icol][k]);
		}
		indxr[i] = irow;
		indxc[i] = icol;
		if (minv[icol][icol] == 0.)
			std::cout << "Error. Singular matrix in MatrixInvert" << std::endl; //Error("Singular matrix in MatrixInvert");

		// Set $m4x4[icol][icol]$ to one by scaling row _icol_ appropriately
		double pivinv = 1.0 / minv[icol][icol];
		minv[icol][icol] = 1.0;
		for (int j = 0; j < 4; j++)
			minv[icol][j] *= pivinv;

		// Subtract this row from others to zero out their columns
		for (int j = 0; j < 4; j++) {
			if (j != icol) {
				double save = minv[j][icol];
				minv[j][icol] = 0;
				for (int k = 0; k < 4; k++)
					minv[j][k] -= minv[icol][k] * save;
			}
		}
	}
	// Swap columns to reflect permutation
	for (int j = 3; j >= 0; j--) {
		if (indxr[j] != indxc[j]) {
			for (int k = 0; k < 4; k++)
				std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
		}
	}
	return Matrix4x4(minv);
}

//// For debugging
//Matrix4x4 m4x4 = Matrix4x4(1, 0, -5, 4, 1, 4, 3, 4, 8, 2, 1, 5, 7, 2, 3, 1);
//
//Matrix4x4 invM = m4x4.Inverse();
//std::cout << invM.m4x4[0][0] << " " << invM.m4x4[0][1] << " " << invM.m4x4[0][2] << " " << invM.m4x4[0][3] << std::endl;
//std::cout << invM.m4x4[1][0] << " " << invM.m4x4[1][1] << " " << invM.m4x4[1][2] << " " << invM.m4x4[1][3] << std::endl;
//std::cout << invM.m4x4[2][0] << " " << invM.m4x4[2][1] << " " << invM.m4x4[2][2] << " " << invM.m4x4[2][3] << std::endl;
//std::cout << invM.m4x4[3][0] << " " << invM.m4x4[3][1] << " " << invM.m4x4[3][2] << " " << invM.m4x4[3][3] << std::endl;