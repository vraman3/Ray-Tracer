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
	INCOMPLETE
	Implementation of the GetIllumination virtual class for the TextureMapping class.

	@param pi: The point of intersection.
	@param ray: The current ray.
	@param n: The normal to the current point of interseciton.
	@param l:
	@param v:
	@param objColour: The colour of the current object.
	@param pointColour:
	@param position:

	@return the colour of the  current point of intersection as a ColourClass.
*/
ColourClass TextureMapping::GetIllumination(VectorClass pi, RayClass ray, VectorClass n, VectorClass l, VectorClass v, ColourClass objColour, ColourClass pointCol, int position)
{
	return ColourClass();
}
