#pragma once

//Author: Vishwanath Raman
#include "VectorClass.h"

class CameraClass
{
private:
	double focalLength;
	VectorClass position;
	VectorClass lookAt;
	VectorClass up;

public:
	CameraClass();
	CameraClass(VectorClass, VectorClass, VectorClass, double);

	double GetFocalLength();
	void   SetFocalLength(double);

	VectorClass GetPosition();
	VectorClass GetLookAt();
	VectorClass GetUpVector();


};

