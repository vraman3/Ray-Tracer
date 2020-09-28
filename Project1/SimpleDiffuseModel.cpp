/**
RayTracing, SimpleDiffuseModel.cpp
Class file to implement an illumination model with only diffuse property for an object.

@author: Vishwanath Raman
@version: 1.0 Oct/30/2019

*/

#include "SimpleDiffuseModel.h"

/**
Parameterized Constructor

@param   paramReflectivity: The parameter for reflectivity of the current object.
@param paramTransmissivity: The parameter for transmissivity of the current object.
*/
SimpleDiffuseModel::SimpleDiffuseModel(double paramReflectivity, double paramTransmissivity) : IlluminationClass(paramReflectivity, paramTransmissivity)
{
}

/**
Implementation of the getIllumination virtual function for SimpleDiffuseModel class.
Always returns the original object colour without calculations.

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
ColourClass SimpleDiffuseModel::getIllumination(VectorClass pi, RayClass ray, VectorClass normal, VectorClass lightRay,
	VectorClass viewerRay, ColourClass objColour, ColourClass pointCol, int maxDepth)
{
	//return ColourClass(0,0,0);


	return objColour;
}