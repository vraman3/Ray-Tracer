#include "IlluminationClass.h"

IlluminationClass::IlluminationClass(double inkr, double inkt)
{
	krReflectivity = inkr;
	ktTransmissivity = inkt;
	//ni = inn;
}

VectorClass IlluminationClass::Reflect(VectorClass incident, VectorClass normal)
{
	double temp = 2.0 * incident.dotProd(normal);

	VectorClass reflectedRay = incident - (normal * temp);

	return reflectedRay;
}