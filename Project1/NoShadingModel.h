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

NoShadingModel::NoShadingModel(double inkr, double inkt, double inn) : IlluminationClass(inkr, inkt, inn)
{}

ColourClass NoShadingModel::GetIllumination(VectorClass pi, RayClass ray, VectorClass N, VectorClass L, VectorClass V, ColourClass objColour, ColourClass pointCol, int position)
{
	//return ColourClass(0,0,0);

	return objColour;
}