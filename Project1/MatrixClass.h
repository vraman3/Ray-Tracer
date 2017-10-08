#pragma once

#include <cmath>
#include <cassert>
#include <vector>
#include <iostream>

#include "VectorClass.h"
class MatrixClass
{
		int mRows, mCols;
		std::vector<std::vector<double>> m;

	public:
				
		MatrixClass(int, int);
		MatrixClass(VectorClass);
				
		MatrixClass operator*(const MatrixClass& a);
		std::vector<double>& operator[](int i);

		static MatrixClass identity(int);
		MatrixClass transpose();
		VectorClass toVector();
};



