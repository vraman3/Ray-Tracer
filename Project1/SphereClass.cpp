
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
	Parameterized Constructor with IlluminationClass. Merge later.

	@param paramRadius: Radius of the sphere.
	@param paramCenter: Position of the center of the sphere.
	@param paramColour: Colour of the sphere.
	@param paramIllum: Illumination model of the sphere.
*/
SphereClass::SphereClass(double paramRadius, VectorClass paramCenter, ColourClass paramColour, IlluminationClass *paramIllum)
{
	illum = paramIllum;
	radius = paramRadius;
	center = paramCenter;
	colour = paramColour;
	diffuse = 0.3;
	specular = 0.6;
	ambient = 0.1;
}

SphereClass::SphereClass(double paramRadius, VectorClass paramCenter)
{
	radius = paramRadius;
	center = paramCenter;
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
	/*

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
	*/

	VectorClass centerToRayOriginVec = ray.GetRayOrigin() - this->center;

	// Since dx2 + dy2 + dz2 = 1 if D is normalized so A = ray.direction DOT ray.direction
	// Vector dotted with itself is equal to squared length of that vector
	double a = ray.GetRayDirection().magnitude_squared();

	double half_b = ray.GetRayDirection().dotProd(centerToRayOriginVec);

	double c = centerToRayOriginVec.magnitude_squared() - this->radius * this->radius;

	double discriminant = (half_b * half_b) - (a * c);

	double W;

	if (discriminant < 0.0)
	{
		return -1;
	}
	else
	{
		double root = sqrt(discriminant);

		W = (-half_b - root) / a;

		if (W > epsilonval_small)
		{
			return W;
		}

		W = (-half_b + root) / a;

		if (W > epsilonval_small)
		{
			return W;
		}
	}

	return -1;
}

/**
	Get the intersection point of the current sphere with a given ray
	if they intersect.

	@return the intersection point between the sphere and the ray, if it exists.
*/
double SphereClass::GetIntersection_d(RayClass ray)
{
	VectorClass centerToRayOriginVec = ray.GetRayOrigin() - this->center;

	// Since dx2 + dy2 + dz2 = 1 if D is normalized so A = ray.direction DOT ray.direction
	// Vector dotted with itself is equal to squared length of that vector
	double a = ray.GetRayDirection().magnitude_squared();

	double b = ray.GetRayDirection().dotProd(centerToRayOriginVec) * 2.0;

	double c = centerToRayOriginVec.magnitude_squared() - this->radius * this->radius;

	double discriminant = (b * b) - (a * c) * 4;

	if (discriminant < 0)
	{
		return -1.0;
	}
	else
	{
		double sqDet = sqrt(discriminant);
		return (-b - sqDet) / (a * 2.0);
	}

}

/**
	Get the intersection point of the current sphere with a given ray
	if they intersect between the given tmin and tmax values

	@return the intersection point between the sphere and the ray, if it exists.
*/
double SphereClass::GetIntersection(RayClass ray, double tmin, double tmax, intersection_record &interRecord)
{
	VectorClass centerToRayOriginVec = ray.GetRayOrigin() - this->center;

	// Since dx2 + dy2 + dz2 = 1 if D is normalized so A = ray.direction DOT ray.direction
	// Vector dotted with itself is equal to squared length of that vector

	double a = ray.GetRayDirection().magnitude_squared();

	double half_b = ray.GetRayDirection().dotProd(centerToRayOriginVec);

	double c = centerToRayOriginVec.magnitude_squared() - this->radius * this->radius;

	double discriminant = (half_b * half_b) - (a * c);

	if (discriminant < 0.0)
	{
		return -1;
	}

	double discriminant_sqrt = sqrt(discriminant);

	// find the root lying between tmin and tmax

	double root = (-half_b - discriminant_sqrt) / a;

	if (root < tmin || tmax < root)
	{
		root = (-half_b + discriminant_sqrt) / a;
		if (root < tmin || tmax < root)
			return -1;
	}

	interRecord.t = root;
	interRecord.point = ray.at(root);
	VectorClass outwardNormal = (interRecord.point - this->center) / radius;
	
	// Check how the normal is. If the ray is hitting from the inside then bool frontFace
	// will be set to false; if ray is hitting from outside then frontFace will be true.
	interRecord.setFaceNormal(ray, outwardNormal);

	return root;
}


/*
*
* 
*		FOR DEBUG ONLY. PLEASE CLEAN.
* 
*/
double SphereClass::GetIntersection_d(RayClass ray, double tmin, double tmax, intersection_record &interRecord)
{
	VectorClass centerToRayOriginVec = ray.GetRayOrigin() - this->center;

	// Since dx2 + dy2 + dz2 = 1 if D is normalized so A = ray.direction DOT ray.direction
	// Vector dotted with itself is equal to squared length of that vector

	double a = ray.GetRayDirection().magnitude_squared();

	double b = ray.GetRayDirection().dotProd(centerToRayOriginVec);

	double c = centerToRayOriginVec.magnitude_squared() - this->radius * this->radius;

	double discriminant = (b * b) - (a * c);

	if (discriminant > 0)
	{
		double discriminant_sqrt = sqrt(discriminant);

		double root = (-b - discriminant_sqrt) / a;

		if (root < tmax && root >tmin)
		{
			interRecord.t = root;
			interRecord.point = ray.at(root);
			interRecord.normal = (interRecord.point - this->center) / radius;
			return true;
		}

		root = (-b + discriminant_sqrt) / a;

		if (root < tmax && root >tmin)
		{
			interRecord.t = root;
			interRecord.point = ray.at(root);
			interRecord.normal = (interRecord.point - this->center) / radius;
			return true;
		}
	}

	return false;
	/*
	if (discriminant < 0.0)
	{
		return -1;
	}

	double discriminant_sqrt = sqrt(discriminant);

	// find the root lying between tmin and tmax

	double root = (-b - discriminant_sqrt) / a;

	if (root < tmin || tmax < root)
	{
		root = (-b + discriminant_sqrt) / a;
		if (root < tmin || tmax < root)
			return -1;
	}

	interRecord.t = root;
	interRecord.point = ray.at(root);
	VectorClass outwardNormal = (interRecord.point - this->center) / radius;
	
	// Check how the normal is. If the ray is hitting from the inside then bool frontFace
	// will be set to false; if ray is hitting from outside then frontFace will be true.
	interRecord.setFaceNormal(ray, outwardNormal);

	return root;*/
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