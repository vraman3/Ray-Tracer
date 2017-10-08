#pragma once

//Author: Vishwanath Raman
#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class PhongModel : public IlluminationClass
{
	private:
		double ka, kd, ks, ke;

	public:
		PhongModel(double, double, double, double, double, double, double);
		ColourClass GetIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

