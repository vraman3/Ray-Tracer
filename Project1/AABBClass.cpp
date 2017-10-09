#include "AABBClass.h"

AABBClass::AABBClass()
{
}

AABBClass::AABBClass(VectorClass min, VectorClass max)
{
	Bmin = min;
	Bmax = max;

	SetCentre();
}

VectorClass AABBClass::GetNormal(VectorClass v = VectorClass(0, 0, 0)){ return v; }

int AABBClass::GetLongestAxis()
{
	double x = Bmax.getX() - Bmin.getX();
	double y = Bmax.getY() - Bmin.getY();
	double z = Bmax.getZ() - Bmin.getZ();

	if (x > y)				// X > Y
	{
		if (x > z)			// X > Z so return X (0)
			return 0;
		else
			return 2;		// Z > X > Y so return Z (2)
	}
	else					// Y > X
	{
		if (y > z)			// Y > Z so return Y (1)
			return 1;
		else
			return 2;		// Z > Y > X so return Z (2)
	}
}

void AABBClass::Expand(AABBClass newBox)
{
	if (newBox.Bmin.getX() < Bmin.getX())
		Bmin.setX(newBox.Bmin.getX());
	if (newBox.Bmin.getY() < Bmin.getY())
		Bmin.setY(newBox.Bmin.getY());
	if (newBox.Bmin.getZ() < Bmin.getZ())
		Bmin.setZ(newBox.Bmin.getZ());

	if (newBox.Bmax.getX() < Bmax.getX())
		Bmax.setX(newBox.Bmax.getX());
	if (newBox.Bmax.getY() < Bmax.getY())
		Bmax.setY(newBox.Bmax.getY());
	if (newBox.Bmax.getZ() < Bmax.getZ())
		Bmax.setZ(newBox.Bmax.getZ());
}

double AABBClass::GetIntersection(RayClass ray, double *hitt0, double *hitt1)
{
	double t0 = ray.minT, t1 = ray.maxT;

	for (int i = 0; i < 3; i++)
	{
		double tNear = (Bmin[i] - ray.GetRayOrigin()[i]) * ray.GetRayInvDirection()[i];
		double tFar = (Bmax[i] - ray.GetRayOrigin()[i]) * ray.GetRayInvDirection()[i];

		if (tNear > tFar)
		{
			double temp = tNear;
			tNear = tFar;
			tFar = temp;
		}

		t0 = tNear > t0 ? tNear : t0;
		t1 = tFar  < t1 ? tFar : t1;
		if (t0 > t1)
		{
			return -1;
		}
	}
	if (hitt0) *hitt0 = t0;
	if (hitt1) *hitt1 = t1;
	//std::cout << " bbox ";
	return t0;
}

double AABBClass::GetIntersection1(RayClass ray, double *hitt0, double *hitt1)
{

	double tmin, tmax, tymin, tymax, tzmin, tzmax;

	// X component
	if (ray.GetRayDirection().getX() >= 0)
	{
		tmin = (Bmin.getX() - ray.GetRayOrigin().getX()) * ray.GetRayInvDirection().getX();
		tmax = (Bmax.getX() - ray.GetRayOrigin().getX()) * ray.GetRayInvDirection().getX();
	}
	else
	{
		tmin = (Bmax.getX() - ray.GetRayOrigin().getX()) * ray.GetRayInvDirection().getX();
		tmax = (Bmin.getX() - ray.GetRayOrigin().getX()) * ray.GetRayInvDirection().getX();
	}

	// Y component
	if (ray.GetRayDirection().getY() >= 0)
	{
		tymin = (Bmin.getY() - ray.GetRayOrigin().getY()) * ray.GetRayInvDirection().getY();
		tymax = (Bmax.getY() - ray.GetRayOrigin().getY()) * ray.GetRayInvDirection().getY();
	}
	else
	{
		tymin = (Bmax.getY() - ray.GetRayOrigin().getY()) * ray.GetRayInvDirection().getY();
		tymax = (Bmin.getY() - ray.GetRayOrigin().getY()) * ray.GetRayInvDirection().getY();
	}

	if ((tmin > tymax) || (tymin > tmax))
	{
		if ((tymin > tmax))
		{
			std::cout << "test ";
		}
		return -1;
	}

	if (tymin > tmin)
		tmin = tymin;
	if (tymax < tmax)
		tmax = tymax;

	// Z component
	if (ray.GetRayDirection().getZ() >= 0)
	{
		tzmin = (Bmin.getZ() - ray.GetRayOrigin().getZ()) * ray.GetRayInvDirection().getZ();
		tzmax = (Bmax.getZ() - ray.GetRayOrigin().getZ()) * ray.GetRayInvDirection().getZ();
	}
	else
	{
		tzmin = (Bmax.getZ() - ray.GetRayOrigin().getZ()) * ray.GetRayInvDirection().getZ();
		tzmax = (Bmin.getZ() - ray.GetRayOrigin().getZ()) * ray.GetRayInvDirection().getZ();
	}

	if ((tmin > tzmax) || (tzmin > tmax))
	{
		std::cout << "bbox returning -1 later";
		return -1;
	}

	if (tzmin > tmin)
		tmin = tzmin;

	if (tzmax < tmax)
		tmax = tzmax;


	if (hitt0) *hitt0 = tmin;
	if (hitt1) *hitt1 = tmax;

	std::cout << "bbox tmin" << tmin;
	return tmin;
}

void AABBClass::SetCentre()
{
	centre.setX((abs(Bmin.getX()) + abs(Bmax.getX())) / 2);
	centre.setY((abs(Bmin.getY()) + abs(Bmax.getY())) / 2);
	centre.setZ((abs(Bmin.getZ()) + abs(Bmax.getZ())) / 2);
}