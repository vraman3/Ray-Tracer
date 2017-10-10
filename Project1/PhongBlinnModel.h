#pragma once

//Author: Vishwanath Raman
#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class PhongBlinnModel : public IlluminationClass
{
	private:
		double ka, kd, ks, ke;

	public:
		PhongBlinnModel(double, double, double, double, double, double);
		ColourClass GetIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

