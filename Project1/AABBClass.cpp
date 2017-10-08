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
	double x = Bmax.GetX() - Bmin.GetX();
	double y = Bmax.GetY() - Bmin.GetY();
	double z = Bmax.GetZ() - Bmin.GetZ();

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
	if (newBox.Bmin.GetX() < Bmin.GetX())
		Bmin.SetX(newBox.Bmin.GetX());
	if (newBox.Bmin.GetY() < Bmin.GetY())
		Bmin.SetY(newBox.Bmin.GetY());
	if (newBox.Bmin.GetZ() < Bmin.GetZ())
		Bmin.SetZ(newBox.Bmin.GetZ());

	if (newBox.Bmax.GetX() < Bmax.GetX())
		Bmax.SetX(newBox.Bmax.GetX());
	if (newBox.Bmax.GetY() < Bmax.GetY())
		Bmax.SetY(newBox.Bmax.GetY());
	if (newBox.Bmax.GetZ() < Bmax.GetZ())
		Bmax.SetZ(newBox.Bmax.GetZ());
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
	if (ray.GetRayDirection().GetX() >= 0)
	{
		tmin = (Bmin.GetX() - ray.GetRayOrigin().GetX()) * ray.GetRayInvDirection().GetX();
		tmax = (Bmax.GetX() - ray.GetRayOrigin().GetX()) * ray.GetRayInvDirection().GetX();
	}
	else
	{
		tmin = (Bmax.GetX() - ray.GetRayOrigin().GetX()) * ray.GetRayInvDirection().GetX();
		tmax = (Bmin.GetX() - ray.GetRayOrigin().GetX()) * ray.GetRayInvDirection().GetX();
	}

	// Y component
	if (ray.GetRayDirection().GetY() >= 0)
	{
		tymin = (Bmin.GetY() - ray.GetRayOrigin().GetY()) * ray.GetRayInvDirection().GetY();
		tymax = (Bmax.GetY() - ray.GetRayOrigin().GetY()) * ray.GetRayInvDirection().GetY();
	}
	else
	{
		tymin = (Bmax.GetY() - ray.GetRayOrigin().GetY()) * ray.GetRayInvDirection().GetY();
		tymax = (Bmin.GetY() - ray.GetRayOrigin().GetY()) * ray.GetRayInvDirection().GetY();
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
	if (ray.GetRayDirection().GetZ() >= 0)
	{
		tzmin = (Bmin.GetZ() - ray.GetRayOrigin().GetZ()) * ray.GetRayInvDirection().GetZ();
		tzmax = (Bmax.GetZ() - ray.GetRayOrigin().GetZ()) * ray.GetRayInvDirection().GetZ();
	}
	else
	{
		tzmin = (Bmax.GetZ() - ray.GetRayOrigin().GetZ()) * ray.GetRayInvDirection().GetZ();
		tzmax = (Bmin.GetZ() - ray.GetRayOrigin().GetZ()) * ray.GetRayInvDirection().GetZ();
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
	centre.SetX((abs(Bmin.GetX()) + abs(Bmax.GetX())) / 2);
	centre.SetY((abs(Bmin.GetY()) + abs(Bmax.GetY())) / 2);
	centre.SetZ((abs(Bmin.GetZ()) + abs(Bmax.GetZ())) / 2);
}