#include "RayClass.h"
#include <cfloat>

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

RayClass::RayClass(VectorClass o, VectorClass d)
{
	minT = 0.0;
	maxT = DBL_MAX;

	origin = o;
	direction = d;
	invDirection.setX(1 / direction.getX());
	invDirection.setY(1 / direction.getY());
	invDirection.setZ(1 / direction.getZ());
}

VectorClass RayClass::GetRayOrigin()
{
	return origin;
}

VectorClass RayClass::GetRayDirection()
{
	return direction;
}

VectorClass RayClass::GetRayInvDirection()
{
	return invDirection;
}