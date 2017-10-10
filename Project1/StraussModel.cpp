/**
	RayTracing, StraussModel.cpp
	Class file to implement Strauss illumination model.

	@author: Vishwanath Raman
	@version: 1.0 Oct/09/2017

*/

#include "StraussModel.h"

/**
	Parameterized constructor.

*/
StraussModel::StraussModel(double paramS, double paramM, double paramT, double paramReflectivity, double paramTransmissivity) : IlluminationClass(paramReflectivity, paramTransmissivity)
{
	smoothness = paramS;
	metalness = paramM;
	transparency = paramT;
	kf = 1.12;
	ks = 1.01;
	debugcounter = 0;
}

/**
	Implementation of the GetIllumination virtual function for PhongModel class.

	@param		  pi: The point of intersection of the ray and the current object.
	@param		 ray: The current ray.
	@param	  normal: The normal to the current point.
	@param	lightRay: The ray from the (current) light source to the intersection point.
	@param viewerRay: Ray from viewer to the intersection point.
	@param objColour: The colour of the current object.
	@param	pointCol: Currently always (1.0,1.0,1.0). Use for light intensity?						INCOMPLETE.
	@param	maxDepth: Maximum depth of the kd-tree, if present.
	@return the colour of the intersection point as a ColourClass.
*/
ColourClass StraussModel::GetIllumination(VectorClass pi, RayClass ray, VectorClass normal, VectorClass lightRay, VectorClass viewerRay, ColourClass objColour, ColourClass pointCol, int maxDepth)
{
	ColourClass tmp = ColourClass(0, 0, 0);

	VectorClass H = Reflect(lightRay, normal);

	double dotNL = normal.dotProd(lightRay);
	double dotNV = normal.dotProd(viewerRay);
	double dotHV = H.dotProd(viewerRay);

	double fdotNL = Fresnel(dotNL);

	
	/*
		The Diffuse component

		diffuse = (N dot L) * d * rDiffuse * C
		rDiffuse = (1 - s^3)(1 - t)
		d = (1 - ms)
	*/
	double s3 = smoothness*smoothness*smoothness;
	double rDiffuse = (1.0 - s3) * (1.0 - transparency);
	double d = (1.0 - metalness * smoothness);

	ColourClass diffuse = objColour * (dotNL * d * rDiffuse);

	/*
		The Specular component

		rn = (1.0 - transparency) - rDiffuse
	*/
	double rn = (1.0 - transparency) - rDiffuse;

	double j = fdotNL * Shadow(dotNL) * Shadow(dotNV);

	double rj = fmin(1.0, rn + j*(rn + 0.1));

	ColourClass c1 = ColourClass(1.0, 1.0, 1.0);

	ColourClass cs  = c1 + (objColour - c1) * metalness * (1.0 - fdotNL);

	ColourClass specular = cs * rj;


	// HOW TO APPROXIMATE POW OF A NEGATIVE BASE AND NON INTEGER EXPONENET
	// WHICH IS A COMPLEX ANSEWER TO A GOD DAMN REAL NUMBER

	//if (smoothness < 1.0)
	specular = specular * pow(-dotHV, 3.0 / (1.0 - smoothness));
	//else
	//specular = specular * pow(-dotHV, 3.0 / 1.0);


	diffuse = pointCol * diffuse;
	specular = pointCol * specular;
	//if (debugcounter < 500)
	//{
	//std::cout << "in " << specular.GetRed() << " " << specular.GetGreen() << " " << specular.GetBlue() << " " << std::endl;
	//std::cout << "in " << diffuse.GetRed() << " " << diffuse.GetGreen() << " " << diffuse.GetBlue() << " " << std::endl;
	//std::cout << "in " << Cs.GetRed() << " " << Cs.GetGreen() << " " << Cs.GetBlue() << " " << std::endl;
	//std::cout << "in " << powl(-dotHV, 3.0 / (1.0 - smoothness)) << std::endl;
	//debugcounter += 50;
	//}

	//##################################################################################################################################################//
	/////////////////////////////
	// AMBIENT IS WRONG.. AFFECTS WHOLE PIC. DEBUG
	ColourClass ambient = objColour * rDiffuse;

	//std::cout << diffuse.GetRed() << " " << diffuse.GetGreen() << " " <<diffuse.GetBlue() << " " << std::endl;

	if (diffuse.GetRed() < 0 || diffuse.GetGreen() < 0 || diffuse.GetBlue() < 0)
		diffuse = ColourClass(0.0, 0.0, 0.0);

	if (specular.GetRed() < 0 || specular.GetGreen() < 0 || specular.GetBlue() < 0)
		specular = ColourClass(0.0, 0.0, 0.0);

	tmp = diffuse;
	/*if (debugcounter < 500)
	{
	std::cout << "in " << tmp.GetRed() << " " << tmp.GetGreen() << " " << tmp.GetBlue() << " " << std::endl;
	debugcounter += 50;
	}*/
	return tmp;
}

double StraussModel::Fresnel(double x)
{
	double a = (1 / (x - kf) * (x - kf)) - (1 / kf*kf);

	//double b1 = 1 / ((1 - kf) * (1 - kf));
	double b = 1 / ((1 - kf) * (1 - kf)) - (1 / kf*kf);

	/*if (debugcounter < 500)
	{
	std::cout << "in " << a/b << std::endl;
	debugcounter += 50;
	}*/
	return a / b;
}

double StraussModel::Shadow(double x)
{

	double a1 = 1 / ((1 - ks) * (1 - ks));
	double a2 = 1 / ((x - ks) * (x - ks));

	double a = a1 - a2;


	double b1 = 1 / ((1 - ks) * (1 - ks));
	double b = b1 - (1 / ks*ks);

	/*if (debugcounter < 500)
	{
	std::cout << "in " << a/b << std::endl;
	debugcounter += 50;
	}*/
	return a / b;
}
