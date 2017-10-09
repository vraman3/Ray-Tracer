#include "SphereClass.h"

SphereClass::SphereClass()
{
	radius = 0.6;
	center = VectorClass(1.0, 1.0, 1.0);
	diffuse = 0.3;
	specular = 0.6;
	ambient = 0.1;
}

SphereClass::SphereClass(double r, VectorClass cent, ColourClass col)
{
	radius = r;
	center = cent;
	colour = col;
	diffuse = 0.3;
	specular = 0.6;
	ambient = 0.1;
}

VectorClass SphereClass::GetNormal(VectorClass point)
{
	//std::cout << center.getX() << " " << center.getY() << " " << center.getZ() << " ";
	return VectorClass((point.getX() - center.getX()), (point.getY() - center.getY()), (point.getZ() - center.getZ()));
}

VectorClass SphereClass::GetCenter(){ return center; }

double SphereClass::GetAmbient(){ return ambient; }

double SphereClass::GetSpecular(){ return specular; }

double SphereClass::GetDiffuse(){ return diffuse; }

ColourClass SphereClass::GetColour(){ return colour; }

double SphereClass::GetIntersection(RayClass ray)
{
	//double A = ray.GetRayDirection().dotProd(ray.GetRayDirection()); // Since dx2 + dy2 + dz2 = 1 if D is normalized
	//
	//double B = 2.0 * (ray.GetRayDirection().dotProd(ray.GetRayOrigin() - this->center));

	//double C = (ray.GetRayOrigin() - this->center).dotProd((ray.GetRayOrigin() - this->center)) - this->radius * this->radius;

	//if (B * B >= 4 * A * C)
	//{
	//	double root = sqrt(B*B - 4 * A*C);

	//	double W1 = (-B - root) / 2 * A;
	//	double W2 = (-B + root) / 2 * A;

	//	if (W1 < 0.00001 && W2 < 0.00001)
	//		return -1;

	//	if (W1 < W2)
	//		return W1;
	//	else
	//		return W2;		
	//}
	//else
	//	return -1;

	double A = ray.GetRayDirection().dotProd(ray.GetRayDirection()); // Since dx2 + dy2 + dz2 = 1 if D is normalized

	VectorClass temp = ray.GetRayOrigin() - this->center;
	double B = 2.0 * (ray.GetRayDirection().dotProd(temp));

	double C = (temp).dotProd(temp) - this->radius * this->radius;

	double check = B*B - 4 * A*C;

	double W;

	if (check < 0.0)
	{
		return -1;
	}
	else
	{
		double root = sqrt(check);
		double denom = 2.0 * A;

		W = (-B - root) / denom;

		if (W > EPSILONVAL)
		{
			return W;
		}

		W = (-B + root) / denom;

		if (W > EPSILONVAL)
		{
			return W;
		}
	}

	return -1;
}