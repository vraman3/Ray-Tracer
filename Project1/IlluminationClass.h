#pragma once

//Author: Vishwanath Raman
#include "ColourClass.h"
#include "RayClass.h"
#include "VectorClass.h"

class IlluminationClass
{
	protected:
		double kr, kt, ni;

	public:
		IlluminationClass()
		{}

		IlluminationClass(double, double, double);

		double Getkr(){ return kr; }

		double Getkt(){ return kt; }

		double Getn(){ return ni; }

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

IlluminationClass::IlluminationClass(double inkr, double inkt, double inn)
{
	kr = inkr;
	kt = inkt;
	ni = inn;
}

VectorClass IlluminationClass::Reflect(VectorClass incident, VectorClass normal)
{
	double temp = 2.0 * incident.DotProd(normal);

	VectorClass reflectedRay = incident - (normal * temp);

	return reflectedRay;
}