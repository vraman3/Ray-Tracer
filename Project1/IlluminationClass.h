#pragma once

//Author: Vishwanath Raman
#include "ColourClass.h"
#include "RayClass.h"
#include "VectorClass.h"

class IlluminationClass
{
	protected:
		double krReflectivity, ktTransmissivity;

	public:
		IlluminationClass()
		{}

		IlluminationClass(double, double);

		double Getkr(){ return krReflectivity; }

		double Getkt(){ return ktTransmissivity; }

		double Getn(){ return 0.0; }

		virtual ColourClass GetIllumination(VectorClass, RayClass, VectorClass, VectorClass, VectorClass, ColourClass, ColourClass, int)
		{			
			return ColourClass(0.0, 0.0, 0.0);
		}

		virtual double GetIntersectData(RayClass ray)
		{
			return 0.0;
		}

		VectorClass Reflect(VectorClass, VectorClass);
};

