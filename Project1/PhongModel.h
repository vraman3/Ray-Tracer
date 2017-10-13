/**
	RayTracing, PhongModel.h
	Header file for PhongModel class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/09/2017

*/

#pragma once

#include "IlluminationClass.h"
#include "ColourClass.h"
#include "VectorClass.h"
#include "RayClass.h"

class PhongModel : public IlluminationClass
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
		PhongModel(double diffuseQuotient, double specularQuotient, double ambientQuotient, double tke, double reflectiveQuotient, double transmissiveQuotient);

		/* Methods */
		ColourClass getIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int);
};

