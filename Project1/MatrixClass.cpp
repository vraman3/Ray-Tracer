#include "MatrixClass.h"

MatrixClass::MatrixClass(int r, int c) : mRows(r), mCols(c), m(std::vector<std::vector<double> >(r, std::vector<double>(c, 0.0)))
{}

MatrixClass::MatrixClass(VectorClass v) : m(std::vector<std::vector<double> >(4, std::vector<double>(1, 1.0))), mRows(4), mCols(1)
{
	m[0][0] = v.GetX();
	m[1][0] = v.GetY();
	m[2][0] = v.GetZ();
}

std::vector<double>& MatrixClass::operator[](int i)
{
	//assert(i >= 0 && i < mRows);
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
		{
		idt.m[i][j] = ((i == j) ? 1.0 : 0.0);
		}

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

VectorClass MatrixClass::toVector()
{
	return VectorClass(m[0][0] / m[3][0], m[1][0] / m[3][0], m[2][0] / m[3][0]);
	//x(m[0][0] / m[3][0]), y(m[1][0] / m[3][0]), z(m[2][0] / m[3][0])
}