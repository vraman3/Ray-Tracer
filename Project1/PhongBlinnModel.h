/**
	RayTracing, PhongBlinnModel.h
	Header file for the PhongBlinn class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/09/2017

*/

#pragma once

#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class PhongBlinnModel : public IlluminationClass
{
	private:
		/* Coefficients 
			
			ka = Ambient coefficient, Background light. 
			kd = Diffuse coefficient, Lambertian reflection.			
			ks = Specular coefficient, mirror-like reflection.
			ke = Specular Hardness. Controls size of specular highlight.
		*/
		double kaAmbient, kdDiffuse, ksSpecular, keHardness;

	public:
		/* Constructors */
		PhongBlinnModel(double, double, double, double, double, double);

		/* Methods */
		ColourClass getIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

