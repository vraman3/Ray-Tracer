/**
	RayTracing, IlluminationClass.h
	Header file for the IlluminationClass.

	@author: Vishwanath Raman
	@version: 1.0 Oct/13/2017

*/
#pragma once

#include "ColourClass.h"
#include "RayClass.h"
#include "VectorClass.h"

class IlluminationClass
{
	protected:
		double krReflectivity, ktTransmissivity;

	public:
		/* Constructors */
		IlluminationClass();
		IlluminationClass(double, double);

		/* Getters */
		double getReflectivitykr();
		double getTransmissivitykt();
		double getNormal();

		/* Virtual functions */
		virtual ColourClass getIllumination(VectorClass pi, RayClass ray, VectorClass normal, VectorClass lightRay, VectorClass viewerRay, ColourClass objColour, ColourClass pointCol, int maxDepth);
		virtual double getIntersectData(RayClass ray);

		/* Methods */
		VectorClass Reflect(VectorClass, VectorClass);
};

