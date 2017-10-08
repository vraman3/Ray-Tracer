#include "IlluminationClass.h"

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