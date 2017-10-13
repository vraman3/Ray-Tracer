/**
	RayTracing, CheckerboardPattern.cpp
	Class to implement a checkerboard pattern on objects.

	@author: Vishwanath Raman
	@version: 1.0 Oct/12/2017

*/
#include "CheckerboardPattern.h"
#include "PhongModel.h"

/**
	Parameterized Constructor.

	@param			paramWidth: Currently unused. Will be removed in future version.
	@param		   paramHeight: Currently unused. Will be removed in future version.
	@param   paramReflectivity: The parameter for reflectivity of the current object.
	@param paramTransmissivity: The parameter for transmissivity of the current object.
*/
CheckerboardPattern::CheckerboardPattern(int paramWidth, int paramHeight, double paramReflectivity, double paramTranmissivity) : IlluminationClass(paramReflectivity, paramTranmissivity)
{
	width  = paramWidth;
	height = paramHeight;
}

/**
	Implementation of the GetIllumination virtual function for the CheckerboardPattern class.
	Uses Phong model as a default for illumination.

	@param			  pi: The point of intersection of the ray and the current object.
	@param			 ray: The current ray.
	@param		  normal: The normal to the current point.
	@param		lightRay: The ray from the (current) light source to the intersection point.
	@param	   viewerRay: Ray from viewer to the intersection point.
	@param	   objColour: The colour of the current object.
	@param		pointCol: Currently always (1,1,1). Use for light intensity?						INCOMPLETE.
	@param		maxDepth: Maximum depth of the kd-tree, if present.
	@param patternChoice: Default: Checkerboard; 1: Smooth colour; 2: Straight lines;
						  3: Straight line w gradient; 4: Donuts; 5: Offset Donuts.
	@return the colour of the intersection point as a ColourClass.
*/
ColourClass CheckerboardPattern::GetIllumination(VectorClass pi, RayClass ray, VectorClass normal, VectorClass lightRay, VectorClass viewerRay, ColourClass objColour, ColourClass pointCol, int maxDepth, int patternChoice=0)
{
	double x = pi.getX();
	double y = pi.getY();
	double z = pi.getZ();
	double size = 1.0;


	PhongModel *p = new PhongModel(0.4, 0.08, 0.3, 12.5, 0.0, 0.0);

	switch (patternChoice)
	{
		//1 Smooth Colour. Merges cos and sin phases		No
	case 1:return p->GetIllumination(pi, ray, normal, lightRay, viewerRay, ColourClass(1.0, 0.0, 0.0) + sin(9 * x)*cos(9 * x), pointCol, maxDepth);
		break;

		//2 Colours straight lines
	case 2:return p->GetIllumination(pi, ray, normal, lightRay, viewerRay, ColourClass(1.0, 0.0, 0.0) + sin(9 * x) + sin(9 * x), pointCol, maxDepth);
		break;

		//3 Straight lines with a smooth gradient change      No
	case 3:return p->GetIllumination(pi, ray, normal, lightRay, viewerRay, ColourClass(1.0, 0.0, 0.0) + sin(9 * x) + sin(9 * x) * sin(9 * x), pointCol, maxDepth);
		break;

		//4 Equally spaced circular donuts with colour in middle
	case 4:return p->GetIllumination(pi, ray, normal, lightRay, viewerRay, ColourClass(1.0, 0.0, 0.0) + sin(9 * x) + sin(9 * x)* sin(9 * z), pointCol, maxDepth);
		break;

		//5 Offset, equally spaced, more dense donuts with colour in middle
	case 5:return p->GetIllumination(pi, ray, normal, lightRay, viewerRay, ColourClass(1.0, 0.0, 0.0) + sin(9 * x)* sin(9 * z) + sin(9 * x)* sin(9 * z), pointCol, maxDepth);
		break;

		//Default checkerboard
	default:
		if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0)
			return p->GetIllumination(pi, ray, normal, lightRay, viewerRay, ColourClass(1.0, 0.0, 0.0), pointCol, maxDepth);
		else
			return p->GetIllumination(pi, ray, normal, lightRay, viewerRay, ColourClass(1.0, 1.0, 0.0), pointCol, maxDepth);
		break;
	}

	/*if (((int)floor(x / size) + (int)floor(y / size) + (int)floor(z / size)) % 2 == 0)
	return p->GetIllumination(pi, ray, N, lightRay, viewerRay, ColourClass(1.0, 0.0, 0.0) + sin(5*x), pointCol, maxDepth);
	else
	return p->GetIllumination(pi, ray, N, lightRay, viewerRay, ColourClass(1.0, 1.0, 0.0) + sin(5*x), pointCol, maxDepth);*/

	// Scale by sin
	//return p->GetIllumination(pi, ray, N, lightRay, viewerRay, ColourClass(1.0, 0.0, 0.0) + sin(9 * x), pointCol, maxDepth);

	// Disco light lol
	//return p->GetIllumination(pi, ray, N, lightRay, viewerRay, ColourClass(sin(x), sin(y), sin(z)), pointCol, maxDepth);

	// Weird wood thing
	/*if ( (int)(x*x + z*z) % 2 == 0)
	return p->GetIllumination(pi, ray, N, lightRay, viewerRay, ColourClass(1.0, 0.0, 0.0), pointCol, maxDepth);
	else
	return p->GetIllumination(pi, ray, N, lightRay, viewerRay, ColourClass(1.0, 1.0, 0.0), pointCol, maxDepth);*/

}