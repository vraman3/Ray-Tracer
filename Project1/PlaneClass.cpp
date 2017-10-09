#include "PlaneClass.h"

PlaneClass::PlaneClass()
{
	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;
}

PlaneClass::PlaneClass(VectorClass vert1, VectorClass vert2, VectorClass vert3, ColourClass col)
{
	A = vert1;
	B = vert2;
	C = vert3;
	edge1 = vert3 - vert1;
	edge2 = vert2 - vert1;

	diffuse = 0.4;
	specular = 0.08;
	ambient = 0.3;

	normal = (edge2.crossProd(edge1)).normalize();
	std::cout << normal.getX() << " " << normal.getY() << " " << normal.getZ() << std::endl;
	colour = col;
	count = 0;
}

VectorClass PlaneClass::GetNormal(VectorClass P)
{
	if (count < 500)
		//std::cout << normal.getX() << " " << normal.getY() << " " << normal.getZ() << std::endl;

		count += 50;
	return normal;

}

double PlaneClass::GetDiffuse()
{
	return diffuse;
}

double PlaneClass::GetSpecular()
{
	return specular;
}

double PlaneClass::GetAmbient()
{
	return ambient;
}

ColourClass PlaneClass::GetColour() { return colour; }

double PlaneClass::GetIntersection(RayClass ray)
{

	//double d = -(normal.dotProd(A));
	//double denom = ray.GetRayDirection().dotProd(normal);
	//double t = 0;
	//if (denom > EPSILONPLANE)
	//{
	//	double num = -normal.dotProd(ray.GetRayOrigin() + normal*d);
	//	//double num = ray.GetRayOrigin().dotProd(normal * d);
	//	double temp = num / denom;
	//	//if (temp > 0)
	//	//{
	//		return temp;
	//	//}
	//}
	//return -1;

	double denom = ray.GetRayDirection().dotProd(normal);
	//std::cout << ray.GetRayDirection().getX() << " ";
	if (denom > EPSILONPLANE)
	{
		VectorClass vec = A - ray.GetRayOrigin();

		double t = vec.dotProd(normal) / denom;

		if (t >= 0)
		{
			//std::cout << t << " ";
			return t;
		}
	}
	return -1;
}


//
///*double areaT = GetArea(A, B, C);
//double areaB = GetArea(A, P, C);
//double areaC = GetArea(A, P, B);
//double areaA = areaT - areaB - areaC;
//
//double c1 = areaA / areaT;
//double c2 = areaB / areaT;
//double c3 = areaC / areaT;
//
//VectorClass NA = (C - A).crossProd(B - A);
//VectorClass NB = (A - B).crossProd(C - B);
//VectorClass NC = (B - C).crossProd(A - C);
//
//double nx = NA.getX() * c1 + NB.getX() * c2 + NC.getX() * c3;
//double ny = NA.getY() * c1 + NB.getY() * c2 + NC.getY() * c3;
//double nz = NA.getZ() * c1 + NB.getZ() * c2 + NC.getZ() * c3;
//
//return VectorClass(nx,ny,nz);*/
//double PlaneClass::GetArea(VectorClass A, VectorClass B, VectorClass C)
//{
//	double a = A.getX() - B.getX() * A.getX() - B.getX() + A.getY() - B.getY() * A.getY() - B.getY() + A.getZ() - B.getZ() * A.getZ() - B.getZ();
//	double b = A.getX() - C.getX() * A.getX() - C.getX() + A.getY() - C.getY() * A.getY() - B.getY() + A.getZ() - B.getZ() * A.getZ() - B.getZ();
//	double c = B.getX() - C.getX() * B.getX() - C.getX() + B.getY() - C.getY() * B.getY() - C.getY() + B.getZ() - C.getZ() * B.getZ() - C.getZ();
//
//	double s = (sqrt(abs(a)) + sqrt(abs(b)) + sqrt(abs(c))) / 2;
//	double area = sqrt(abs(s * (s - a) * (s - b) * (s - c)));
//
//	return area;
//}
