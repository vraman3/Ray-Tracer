/**
	RayTracing, CameraClass.cpp
	Class containing attributes for Camera system.

	@author: Vishwanath Raman
	@version: 1.0 Oct/12/2017

*/

#include "CameraClass.h"

/**
	Default Constructor
*/
CameraClass::CameraClass()
{
	focalLength = 2.0;
	position = VectorClass(0, 0, 0);
	lookAt = VectorClass(0, 0, -1);
	up = VectorClass(0, 1, 0);
}

/**
	Parameterized Constructor

	@param	  paramPosition: Coordinates for position of the camera.
	@param		paramLookAt: The lookat vector of the Camera.
	@param			paramUp: The up vector of the camera.
	@param paramFocalLength: The focal length of the camera.
*/
CameraClass::CameraClass(VectorClass paramPosition, VectorClass paramLookAt, VectorClass paramUp, double paramFocalLength)
{
	focalLength = paramFocalLength;
	position = paramPosition;
	lookAt = paramLookAt;
	up = paramUp;
}

/**
	Get the focal length of the current camera.

	@return the focal length of the current camera.
*/
double CameraClass::GetFocalLength()   { return focalLength; }

/**
	Get the coordinates for position of the current camera.

	@return the coordinates for position of the current camera.
*/

VectorClass CameraClass::GetPosition() { return position; }

/**
	Get the look at vector of the current camera.

	@return the look at vector of the current camera
*/
VectorClass CameraClass::GetLookAt()   { return lookAt; }

/**
	Get the up vector of the current camera.

	@return the up vector of the current camera.
*/
VectorClass CameraClass::GetUpVector() { return up; }

/**
	Set the focal length of the camera.
	
	@param paramFocalLength: The value to be set as the focal length.
	
*/
void CameraClass::SetFocalLength(double f) { focalLength = f; }