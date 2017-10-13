/**
	RayTracing, TextureMapping.cpp
	Class file for Texture Mapping.

	@author: Vishwanath Raman
	@version: 1.0 Oct/09/2017

*/

#include "TextureMapping.h"

/**
	Parameterized constructor for TextureMapping class.

	@param paramU: Input parameter for 'u'.
	@param paramV: Input parameter for 'v'.
*/
TextureMapping::TextureMapping(double paramU, double paramV)
{
	u = paramU;
	v = paramV;
}

/**
	Implementation of the getIllumination virtual function for TextureMapping class.

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
ColourClass TextureMapping::getIllumination(VectorClass pi, RayClass ray, VectorClass normal, VectorClass lightRay, VectorClass viewerRay, ColourClass objColour, ColourClass pointCol, int maxDepth)
{
	return ColourClass();
}
