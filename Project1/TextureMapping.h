#pragma once

//Author: Vishwanath Raman
#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class TextureMapping :public IlluminationClass
{
	private:
		double u, v;

	public:
		TextureMapping(double, double);
		ColourClass GetIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

