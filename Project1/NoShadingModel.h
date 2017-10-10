/**
	RayTracing, NoShadingModel.h
	Header file for the NoShadingModel class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/10/2017

*/

#pragma once

#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class NoShadingModel :public IlluminationClass
{
	public:
		/* Constructors */
		NoShadingModel(double, double);

		/* Methods */
		ColourClass GetIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

