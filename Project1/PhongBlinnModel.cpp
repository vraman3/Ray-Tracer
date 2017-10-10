/**
	RayTracing, PhongBlinnModel.cpp
	Class file to implement the Phong-Blinn illumination model.

	@author: Vishwanath Raman
	@version: 1.0 Oct/09/2017

*/

#include "PhongBlinnModel.h"

/**
	Parameterized constructor.

	@param		  paramDiffuse: The parameter for diffuse value (Lambertian reflection) of the current object.
	@param		 paramSpecular: The parameter for specular value (mirror-like reflection) of the current object.
	@param		  paramAmbient: The parameter for ambient value (background light) of the current object.
	@param   paramSpecHardness: The parameter for the specular hardness of the current object.
	@param   paramReflectivity: The parameter for reflectivity of the current object.
	@param paramTransmissivity: The parameter for transmissivity of the current object.
*/
PhongBlinnModel::PhongBlinnModel(double paramDiffuse, double paramSpecular, double paramAmbient, double paramSpecHardness, double paramReflectivity, double paramTransmissivity) : IlluminationClass(paramReflectivity, paramTransmissivity)
{
	kaAmbient = paramAmbient;
	kdDiffuse = paramDiffuse;
	ksSpecular = paramSpecular;
	keHardness = paramSpecHardness;
}

/**
	Implementation of the GetIllumination virtual function for PhongModel class.

	@param		  pi: The point of intersection of the ray and the current object.
	@param		 ray: The current ray.
	@param	  normal: The normal to the current point.
	@param	lightRay: The ray from the (current) light source to the intersection point.
	@param viewerRay: Ray from viewer to the intersection point.
	@param objColour: The colour of the current object.
	@param	pointCol: Currently always (1,1,1). Use for light intensity?						INCOMPLETE.
	@param	maxDepth: Maximum depth of the kd-tree, if present.
	@return the colour of the intersection point as a ColourClass.
*/
ColourClass PhongBlinnModel::GetIllumination(VectorClass pi, RayClass ray, VectorClass normal, VectorClass lightRay, VectorClass viewerRay, ColourClass objColour, ColourClass pointCol, int maxDepth)
{
	ColourClass tmp = ColourClass(0.0, 0.0, 0.0);
	//double kdDiffuse = objects[closest]->GetDiffuse();
	//double ksSpecular = objects[closest]->GetSpecular();
	//double kaAmbient = objects[closest]->GetAmbient();

	/*if (closest == 2 && testCounter < 500)
	{
	std::cout << kdDiffuse << " dnl" << std::endl;
	testCounter += 50;
	}*/
	if (ray.GetRayDirection().dotProd(normal) < 0)
	{
		if (kdDiffuse > 0)
		{
			double dotNL = normal.dotProd(lightRay);

			/*if (closest == 2 && testCounter < 500)
			{
			std::cout << dotNL << " dnl" << std::endl;
			testCounter += 50;
			}*/
			if (dotNL > 0)
			{
				double diff = kdDiffuse * dotNL;
				ColourClass diffuse = objColour * diff * pointCol;

				tmp = tmp + diffuse;

				//VectorClass V = (ray.GetRayOrigin() - pi).normalize();			

				VectorClass temp = (lightRay + viewerRay).normalize();			//1//
				VectorClass R = temp / temp.magnitude();						//2//  For Phong-Blinn
				double dotVR = R.dotProd(normal);								//3//		

				//VectorClass R = (N * 2 * dotNL - L).normalize();				//1//	For Phong
				//double dotVR = R.dotProd(V);									//2//


				if (dotVR > 0)
				{
					double spec = ksSpecular * pow(dotVR, keHardness);
					ColourClass specular = (ColourClass(1.0, 1.0, 1.0) * spec) * pointCol;
					tmp = tmp + specular;
				}

			}
		}
		ColourClass ambient = (objColour * kaAmbient)* pointCol;
		tmp = tmp + ambient;

		return tmp;
	}
	else
	{
		double dotNL = normal.dotProd(lightRay);

		//if (dotNL > 0.0001)
		//{
		if (ktTransmissivity == 1.0)
		{
			VectorClass R = (normal * 2 * dotNL - lightRay).normalize();			//1//	For Phong
			double dotVR = R.dotProd(viewerRay);									//2//


			if (dotVR > 0.0001)
			{
				double spec = ksSpecular * pow(dotVR, keHardness);
				ColourClass specular = (ColourClass(1.0, 1.0, 1.0) * spec) * pointCol;
				tmp = tmp + specular;
			}
		}
		return tmp;
	}
}