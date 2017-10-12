/**
	RayTracing, CameraClass.h
	Header file for the CamerClass.

	@author: Vishwanath Raman
	@version: 1.0 Oct/12/2017

*/
#pragma once

#include "VectorClass.h"

class CameraClass
{
private:
	double focalLength;
	VectorClass position;
	VectorClass lookAt;
	VectorClass up;

public:
	/* Constructors */
	CameraClass();
	CameraClass(VectorClass, VectorClass, VectorClass, double);

	/* Getters */
	double GetFocalLength();
	VectorClass GetPosition();
	VectorClass GetLookAt();
	VectorClass GetUpVector();

	/* Setters */
	void   SetFocalLength(double);
};

