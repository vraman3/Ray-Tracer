/**
	RayTracing, ObjectClass.cpp
	The base ObjectClass for all objects. All objects will
	inherit from this class to make sure each object has the
	required functions for rruntime polymorphism.

	@author: Vishwanath Raman
	@version: 1.0 Oct/21/2017

*/
#include "ObjectClass.h"

ObjectClass::ObjectClass()
{
	albedo = 0.18;
}
/**
	Get the ambient quotient value for current object.

	@return the ambient quotient for current object.
*/
double ObjectClass::GetAmbient()
{
	return 0.0;
}

/**
	Get the specular quotient value for current object.

	@return the specular quotient for current object.
*/
double ObjectClass::GetSpecular()
{
	return 0.0;
}

/**
	Get the diffuse quotient value for current object.

	@return the diffuse quotient for current object.
*/
double ObjectClass::GetDiffuse()
{
	return 0.0;
}

/**
	Get the normal at a point on the current current object.

	@return the normal as VectorClass.
*/
VectorClass ObjectClass::GetNormal(VectorClass paramPi)
{
	return VectorClass(0, 0, 0);
}

/**
	Get the colour of current object.

	@return the colour for current object.
*/
ColourClass ObjectClass::GetColour()
{
	return ColourClass(0, 0, 0);
}

/**
	Get the intersection of the current object with a ray.

	@return the distance of the intersection of the current object and given ray,
	along the ray.
*/
double ObjectClass::GetIntersection(RayClass paramRay)
{
	return 0.0;
}

/**
	Get the intersection of the current object with a ray for given tmin and tmax values

	@return the distance of the intersection of the current object and given ray,
	along the ray.
*/
double ObjectClass::GetIntersection(RayClass paramRay, double tmin, double tmax, intersection_record &interRecord)
{
	return 0.0;
}

/**
	Get the midpoint of the current object.

	@return the midpoint of the current object as VectorClass.
*/
VectorClass ObjectClass::GetMidpoint()
{
	return VectorClass();
}