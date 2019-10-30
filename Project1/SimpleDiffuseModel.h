/**
RayTracing, SimpleDiffuseModel.h
Header file for the SimpleDiffuseModel class.

@author: Vishwanath Raman
@version: 1.0 Oct/30/2019

*/
#pragma once

#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class SimpleDiffuseModel :public IlluminationClass
{
public:
	/* Constructors */
	SimpleDiffuseModel(double, double);

	/* Methods */
	ColourClass getIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

