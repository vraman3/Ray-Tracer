/**
	RayTracing, MatrixClass.h
	Header file to implement MatrixClass.

	@author: Vishwanath Raman
	@version: 1.0 Oct/13/2017

*/
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
		/* Constructors */
		MatrixClass(int, int);
		MatrixClass(VectorClass);
		
		/* Operator Overloading */
		MatrixClass operator*(const MatrixClass& a);
		std::vector<double>& operator[](int i);

		/* Methods */
		static MatrixClass identity(int);
		MatrixClass transpose();
		VectorClass toVector();
};



