/**
	RayTracing, IlluminationClass.cpp
	Base class for Illumination models. Other illumination models
	will inherit this base class.

	@author: Vishwanath Raman
	@version: 1.0 Oct/13/2017

*/
#include "IlluminationClass.h"

/**
	Default Constructor. Reflectivity is 30% and tranmissivity is 0.
	Slightly reflective opaque object.
*/
IlluminationClass::IlluminationClass()
{
	krReflectivity = 0.3;
	ktTransmissivity = 0.0;
}

/**
	Parameterized constructor.

	@param   paramReflectivity: The parameter for reflectivity of the current object.
	@param paramTransmissivity: The parameter for transmissivity of the current object.
*/
IlluminationClass::IlluminationClass(double paramReflectivity, double paramTranmissivity)
{
	krReflectivity = paramReflectivity;
	ktTransmissivity = paramTranmissivity;
}

/**
	Get the reflectivity coefficient, krReflectivity, of the current object.

	@return the reflectivity coefficient, krReflectivity.
*/
double IlluminationClass::getReflectivitykr()
{ 
	return krReflectivity; 
}

/**
	Get the transmissivity coefficient, ktTransmissivity, of the current object.

	@return the transmissivity coefficient, ktTransmissivity .
*/
double IlluminationClass::getTransmissivitykt()
{ 
	return ktTransmissivity;
}

/**
	Get the normal. Currently unused. Remove in future version.

	@return the normal. Not used.
*/
double IlluminationClass::getNormal()
{ 
	return 0.0;
}

/**
	Virtual function getIllumination() that can be implemented by different illumination 
	model classes inheriting this class.

	@param		  pi: The point of intersection of the ray and the current object.
	@param		 ray: The current ray.
	@param	  normal: The normal to the current point.
	@param	lightRay: The ray from the (current) light source to the intersection point.
	@param viewerRay: Ray from viewer to the intersection point.
	@param objColour: The colour of the current object.
	@param	pointCol: Currently always (1,1,1). Use for light intensity?						INCOMPLETE.
	@param	maxDepth: Maximum depth of the kd-tree, if present.
	@return the colour of the intersection point as a ColourClass.
*/
ColourClass IlluminationClass::getIllumination(VectorClass pi, RayClass ray, VectorClass normal, VectorClass lightRay, VectorClass viewerRay, ColourClass objColour, ColourClass pointCol, int maxDepth)
{			
	return ColourClass(0.0, 0.0, 0.0);
}

/**
	Virtual function. Currently unused. Remove in future version.

	@param ray: Ray to be intersected with.
	@return the interseciton point colour?
*/
double IlluminationClass::getIntersectData(RayClass ray)
{
	return 0.0;
}

/**
	This function will calculate the reflected ray, given an incident ray and
	the normal the point of intersection.

	@param paramIncident: The incident ray.
	@param   paramNormal: The normal to the point of intersection.
	@return the reflected ray.
*/
VectorClass IlluminationClass::Reflect(VectorClass paramIncident, VectorClass paramNormal)
{
	double temp = 2.0 * paramIncident.dotProd(paramNormal);

	VectorClass reflectedRay = paramIncident - (paramNormal * temp);

	return reflectedRay;
}