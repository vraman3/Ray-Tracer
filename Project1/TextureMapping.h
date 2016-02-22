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

TextureMapping::TextureMapping(double inu, double inv)
{
	u = inu;
	v = inv;
}

ColourClass TextureMapping::GetIllumination(VectorClass pi, RayClass ray, VectorClass N, VectorClass L, VectorClass V, ColourClass objColour, ColourClass pointCol, int position)
{

}
