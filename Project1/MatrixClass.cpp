/**
	RayTracing, MatrixClass.cpp
	Implement a class for matrix storage and operations.

	@author: Vishwanath Raman
	@version: 1.0 Oct/13/2017

*/
#include "MatrixClass.h"

/**
	Default Constructor.
*/
MatrixClass::MatrixClass(int paramRows, int paramColumns) : mRows(paramRows), mCols(paramColumns), m(std::vector<std::vector<double> >(paramRows, std::vector<double>(paramColumns, 0.0)))
{}

/**
	Parameterized Constructor.
*/
MatrixClass::MatrixClass(VectorClass paramInputVector) : m(std::vector<std::vector<double> >(4, std::vector<double>(1, 1.0))), mRows(4), mCols(1)
{
	m[0][0] = paramInputVector.getX();
	m[1][0] = paramInputVector.getY();
	m[2][0] = paramInputVector.getZ();
}

/**
	INCOMPLETE TEST FOR MULTIPLE DIMENSIONS
	Operator Overloading for getting the dimensions of the matrix.
	( [] )

	@param paramDimension: The dimension of the element to be returned, 0,1,2.
	@return the element for the dimension specified
*/
std::vector<double>& MatrixClass::operator[](int paramDimension)
{
	//assert(i >= 0 && i < mRows);
	return m[paramDimension];
}
//double& MatrixClass::operator()(int i, int j)
//{
//	return m[i * mCols + j];
//}
//
//double MatrixClass::operator()(int i, int j) const
//{
//	return m[i * mCols + j];
//}

/**
	Create an identity matrix.

	@param paramSize: The size of the identity matrix.
	@return the identity matrix.
*/
MatrixClass MatrixClass::identity(int paramSize)
{
	MatrixClass idt(paramSize, paramSize);

	for (int i = 0; i < paramSize; i++)
		for (int j = 0; j < paramSize; j++)
		{
		idt.m[i][j] = ((i == j) ? 1.0 : 0.0);
		}

	return idt;
}

/**
	Operator overloading to multiple two matrices.

	@param paramB: The matrix to be multipled with.
	@return the result of multiplication of the two matrices.
*/
MatrixClass MatrixClass::operator*(const MatrixClass& paramB)
{
	assert(mCols == paramB.mRows);

	MatrixClass result(mRows, paramB.mCols);

	for (int i = 0; i < mRows; i++)
		for (int j = 0; j < paramB.mCols; j++)
		{
		result.m[i][j] = 0.0;
		for (int k = 0; k < mCols; k++)
		{
			result.m[i][j] += m[i][k] * paramB.m[k][j];
		}
		}

	return result;
}

/**
	Create the tranpose of current matrix.

	@return the tranpose of the current matrix.
*/
MatrixClass MatrixClass::transpose()
{
	MatrixClass result(mCols, mRows);

	for (int i = 0; i < mRows; i++)
		for (int j = 0; j < mCols; j++)
			result.m[j][i] = m[i][j];

	return result;
}

/**
	INCOMPLETE
*/
VectorClass MatrixClass::toVector()
{
	return VectorClass(m[0][0] / m[3][0], m[1][0] / m[3][0], m[2][0] / m[3][0]);
}