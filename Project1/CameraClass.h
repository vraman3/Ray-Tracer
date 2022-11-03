/**
	RayTracing, CameraClass.h
	Header file for the CamerClass.

	@author: Vishwanath Raman
	@version: 1.0 Oct/12/2017

*/
#pragma once

#include "VectorClass.h"
#include "MatrixClass.h"
#include "RayClass.h"

class CameraClass
{
private:
	double focalLength;
	VectorClass position;
	VectorClass lookAt;
	VectorClass up;

	VectorClass origin;
	VectorClass lowerLeftCorner;
	VectorClass horizontal;
	VectorClass vertical;

public:
	/* Constructors */
	CameraClass();
	CameraClass(int parameterDebug, VectorClass position, VectorClass lookat, VectorClass up, double vfov, double aspectRatio);
	CameraClass(VectorClass camPosition, VectorClass lookat, VectorClass upVector, double focallength);
	CameraClass(double vfov, double aspectRatio);

	/* Getters */
	double GetFocalLength();
	VectorClass GetPosition();
	VectorClass GetLookAt();
	VectorClass GetUpVector();

	/* Setters */
	void   SetFocalLength(double);

	/* Methods */
	RayClass getRay(double u, double v);
	MatrixClass viewPort(int x, int y, int w, int h, int depth);
	MatrixClass calcLookAt(VectorClass eye, VectorClass centre, VectorClass up);
};

