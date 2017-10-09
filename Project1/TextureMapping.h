/**
	RayTracing, TextureMapping.h
	Header file for TextureMapping class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/09/2017

*/

#pragma once

#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class TextureMapping :public IlluminationClass
{
	private:
		double u, v;

	public:
		/* Constructor */
		TextureMapping(double, double);

		/* Methods */
		ColourClass GetIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

