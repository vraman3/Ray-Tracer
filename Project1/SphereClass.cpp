
/**
	RayTracing, SphereClass.cpp
	The class file to implement a Sphere.

	@author: Vishwanath Raman
	@version: 1.0 Oct/10/2017

*/

#include "SphereClass.h"

/**
	Default constructor.
*/
SphereClass::SphereClass()
{
	radius = 0.6;
	center = VectorClass(1.0, 1.0, 1.0);
	diffuse = 0.3;
	specular = 0.6;
	ambient = 0.1;
}

/**
	Parameterized Constructor.

	@param paramRadius: Radius of the sphere.
	@param paramCenter: Position of the center of the sphere.
	@param paramColour: Colour of the sphere.
*/
SphereClass::SphereClass(double paramRadius, VectorClass paramCenter, ColourClass paramColour)
{
	radius = paramRadius;
	center = paramCenter;
	colour = paramColour;
	diffuse = 0.3;
	specular = 0.6;
	ambient = 0.1;
}

/**
	Get the normal at a point on the sphere.

	@param point: The point at which to calculate the normal.
	@return the normal at the given point, as a VectorClass
*/
VectorClass SphereClass::GetNormal(VectorClass point)
{
	//std::cout << center.getX() << " " << center.getY() << " " << center.getZ() << " ";
	return VectorClass((point.getX() - center.getX()), (point.getY() - center.getY()), (point.getZ() - center.getZ()));
}

/**
	Get the center of the sphere.

	@return the center of the sphere.
*/
VectorClass SphereClass::GetCenter(){ return center; }

/**
	Get the ambient coefficient of the sphere.

	@return the ambient coefficient of the sphere.
*/
double SphereClass::GetAmbient(){ return ambient; }

/**
	Get the specular coefficient of the sphere.

	@return the specular coefficient of the sphere.
*/
double SphereClass::GetSpecular(){ return specular; }

/**
	Get the diffuse coefficient of the sphere.

	@return the diffuse coefficient of the sphere.
*/
double SphereClass::GetDiffuse(){ return diffuse; }

/**
	Get the colour of the sphere.

	@return the colour of the sphere.
*/
ColourClass SphereClass::GetColour(){ return colour; }

/**
	Get the intersection point of the current sphere with a given ray
	if they intersect.

	@return the intersection point between the sphere and the ray, if it exists.
*/
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

/**
	Set the diffuse coefficient of the sphere.

	@param paramDiffuse: The diffuse coefficient to be set.
*/
void SphereClass::SetDiffuse(double paramDiffuse)
{
	diffuse = paramDiffuse;
}

/**
	Set the specular coefficient of the sphere.

	@param paramSpecular: The specular coefficient to be set.
*/
void SphereClass::SetSpecular(double paramSpecular)
{
	specular = paramSpecular;
}

/**
	Set the diffuse coefficient of the sphere.

	@param paramAmbient: The ambient coefficient to be set.
*/
void SphereClass::SetAmbient(double paramAmbient)
{
	ambient = paramAmbient;
}