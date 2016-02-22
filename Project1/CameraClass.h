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

CameraClass::CameraClass()
{
	focalLength = 2.0;
	position = VectorClass(0, 0, 0);
	lookAt   = VectorClass(0, 0, -1);
	up		 = VectorClass(0, 1, 0);
}

CameraClass::CameraClass(VectorClass p, VectorClass l, VectorClass u, double f)
{
	focalLength = f;
	position = p;
	lookAt = l;
	up = u;
}

VectorClass CameraClass::GetPosition() {	return position; }

VectorClass CameraClass::GetLookAt()   {	return lookAt; }

VectorClass CameraClass::GetUpVector() {	return up; }

double CameraClass::GetFocalLength()   {	return focalLength; }

void CameraClass::SetFocalLength(double f) {	focalLength = f; }