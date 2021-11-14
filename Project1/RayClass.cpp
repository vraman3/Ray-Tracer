/**
	RayTracing, RayClass.cpp
	Class to store and implement a Ray.

	@author: Vishwanath Raman
	@version: 1.0 Oct/21/2017

*/
#include "RayClass.h"
#include <cfloat>

/**
	Default constructor.
*/
RayClass::RayClass()
{
	minT = 0.0;
	maxT = DBL_MAX;

	origin = VectorClass(0, 0, 0);
	direction = VectorClass(1, 0, 0);
	invDirection.setX(1 / direction.getX());
	invDirection.setY(1 / direction.getY());
	invDirection.setZ(1 / direction.getZ());
}

/**
	Parameterized constructor.

	@param	  paramOrigin: The coordiantes for origin of the current ray.
	@param paramDirection: The direction vector for the current ray.
*/
RayClass::RayClass(VectorClass paramOrigin, VectorClass paramDirection)
{
	minT = 0.0;
	maxT = DBL_MAX;

	origin = paramOrigin;
	direction = paramDirection;
	invDirection.setX(1 / direction.getX());
	invDirection.setY(1 / direction.getY());
	invDirection.setZ(1 / direction.getZ());
}

/**
	Get the origin of the current ray.

	@return the coordinates of origin of the current ray.
*/
VectorClass RayClass::GetRayOrigin()
{
	return origin;
}

/**
	Get the direction of the current ray.

	@return the coordinates of direction vector of the current ray.
*/
VectorClass RayClass::GetRayDirection()
{
	return direction;
}

/**
	Get the inverse of the direction of the current ray.

	@return the coordinates of the inverse direction of the current ray.
*/
VectorClass RayClass::GetRayInvDirection()
{
	return invDirection;
}

/**
	Set the origin of the current ray with the new given origin.

	@param paramOrigin:	The new origin to be set.
*/
void RayClass::SetRayOrigin(VectorClass paramOrigin)
{
	origin = paramOrigin;
}

/**
	Set the direction of the current ray with the new given direction.
	The inverse is re-calculated using the new direction.

	@param paramDirection:	The new direction to be set.
*/
void RayClass::SetRayDirection(VectorClass paramDirection)
{
	direction = paramDirection;

	invDirection.setX(1 / direction.getX());
	invDirection.setY(1 / direction.getY());
	invDirection.setZ(1 / direction.getZ());
}

VectorClass RayClass::at(double t)
{
	return this->origin + this->direction * t;
}