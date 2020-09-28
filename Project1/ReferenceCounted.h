/**
RayTracing, ReferenceCounted.cpp
Header file for ReferenceCounted.

Taken from/Based on the PBRT book by Matt Pharr and Greg Humphreys.

@author: Vishwanath Raman
@version: 1.0 Mar/18/2018

*/

#pragma once

class ReferenceCounted
{
private:
	/* Methods */
	ReferenceCounted(const ReferenceCounted&);
	//ReferenceCounted &operator=(const ReferenceCounted&);

public:
	/* Variables */
	int nReferences;

	/* Constructors */
	ReferenceCounted()
	{
		nReferences = 0;
	}
	
};