/**
	RayTracing, StraussModel.h
	Header file for the StraussModel class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/09/2017

*/

#pragma once

#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class StraussModel : public IlluminationClass
{
	private:

		/*
			smoothness   (s) = Describes roughness of surface;
			0 = perfectly diffuse;
			1 = perfectly specular.
			metlanness   (m) = Affects colour of specular highlight;
			0 = non-metallic (specular highlight = colour of light);
			1 = metallic (specular highlight = based on color of object,
							  especially at given reflection angles).
			transparency (t) = 0 = Solid; 1 = Fully transparent.
		*/
		double smoothness, metalness, transparency, kf, ks;

	public:
		double debugcounter;

		/* Constructors */
		StraussModel(double, double, double, double, double);

		/* Methods */
		ColourClass getIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
		double Fresnel(double);
		double Shadow(double);
};

