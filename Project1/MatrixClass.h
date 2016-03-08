#pragma once

#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>
class MatrixClass
{
		int mRows, mCols;
		std::vector<std::vector<double>> m;
	public:
		std::vector<double>& operator[](int i);
		MatrixClass(int, int);
		static MatrixClass identity(int);
	/*	double& operator()(int, int);
		double operator()(int, int) const;*/
		
		MatrixClass operator*(const MatrixClass& a);
		MatrixClass MatrixClass::transpose();
};

MatrixClass::MatrixClass(int r, int c) : mRows(r), mCols(c), m(r*c)
{}

std::vector<double>& MatrixClass::operator[](int i)
{
	assert(i > 0 && i < mRows);
	return m[i];
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

MatrixClass MatrixClass::identity(int dimension)
{
	MatrixClass idt(dimension, dimension);

	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			idt.m[i][j] = (i == j ? 1.0 : 0.0);

	return idt;
}

MatrixClass MatrixClass::operator*(const MatrixClass& a)
{
	assert(mCols == a.mRows);

	MatrixClass result(mRows, a.mCols);

	for (int i = 0; i < mRows; i++)
		for (int j = 0; j < a.mCols; j++)
		{
			result.m[i][j] = 0.0;
			for (int k = 0; k < mCols; k++)
			{
				result.m[i][j] += m[i][k] * a.m[k][j];
			}
		}

	return result;
}

MatrixClass MatrixClass::transpose()
{
	MatrixClass result(mCols, mRows);

	for (int i = 0; i < mRows; i++)
		for (int j = 0; j < mCols; j++)
			result.m[j][i] = m[i][j];

	return result;
}