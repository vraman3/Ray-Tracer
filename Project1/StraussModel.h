#pragma once

//Author: Vishwanath Raman
#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class StraussModel : public IlluminationClass
{
	private:
		double s, m, t, kf, ks;

	public:
		double debugcounter;
		StraussModel(double, double, double, double, double, double);
		ColourClass GetIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
		double Fresnel(double);
		double Shadow(double);
};

