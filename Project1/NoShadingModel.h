#pragma once

//Author: Vishwanath Raman
#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class NoShadingModel :public IlluminationClass
{
	//private:

	public:
		NoShadingModel(double, double, double);
		ColourClass GetIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

