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

	@param	parameterDebug: Integer parameter just to signify that this constructor is for the
							debug class.
*/
CameraClass::CameraClass(int parameterDebug, VectorClass paramPosition, VectorClass paramLookat, VectorClass paramUp, double vfov, double aspectRatio)
{
	//double aspectRatio = 16.0 / 9.0;
	// degrees_to_radians = degrees  * pi / 180.0;
	// pi = 3.1415926535897932385
	auto theta = vfov * 3.1415926535897932385 / 180.0;
	auto h = tan(theta / 2);

	double viewportHeight = 2.0 * h;
	double viewportWidth = aspectRatio * viewportHeight;
	focalLength = 1.0;

	VectorClass w = (paramPosition - paramLookat).normalize();
	VectorClass u = (paramUp.crossProd(w)).normalize();
	VectorClass v = w.crossProd(u);

	origin = paramPosition;//VectorClass(0.0, 0.0, 0.0);
	horizontal = u * viewportWidth;
	vertical = v * viewportHeight;

	lowerLeftCorner = origin - horizontal / 2 - vertical / 2 - w;
}
/*
*
* 
*	DEBUG PLEASE CLEAN
* 
* 	
*/
CameraClass::CameraClass(double vfov, double aspectRatio)
{
	//double aspectRatio = 16.0 / 9.0;
	// degrees_to_radians = degrees  * pi / 180.0;
	// pi = 3.1415926535897932385
	auto theta = vfov * 3.1415926535897932385 / 180.0;
	auto half_height = tan(theta / 2);

	double half_width = aspectRatio * half_height;

	lowerLeftCorner = VectorClass(-half_width, -half_height, -1.0);
	horizontal = VectorClass(2 * half_width, 0.0, 0.0);
	vertical = VectorClass(0.0, 2 * half_height, 0.0);
	origin = VectorClass(0.0, 0.0, 0.0);

	//lowerLeftCorner = VectorClass(-2.0, -1.0, -1.0);
	//horizontal = VectorClass(4.0, 0.0, 0.0);
	//vertical = VectorClass(0.0, 2.0, 0.0);
	//origin = VectorClass(0.0, 0.0, 0.0);

	focalLength = -1;
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
	Parameterized Constructor

	@param		paramPosition: Coordinates for position of the camera.
	@return		This function returns a ray with the camera origin and calculates the direction
				using the passed u and v parameters
*/
RayClass CameraClass::getRay(double u, double v)
{
	VectorClass direction = lowerLeftCorner + horizontal * u + vertical * v - origin;

	return RayClass(origin, direction);
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

/**
	Calculate the viewPort for the current Camera.

	Currently unused and incomplete.

	@param x: x coordinate.
	@param y: y coordinate.
	@param w: width of the screen.
	@param h: height of the screen.
	@param depth: depth.
	@return the viewPort as a Matrix.
*/
MatrixClass viewPort(int x, int y, int w, int h, int depth)
{
	MatrixClass vp = MatrixClass::identity(4);
	vp[0][3] = x + (w / 2.0);
	vp[1][3] = y + (h / 2.0);
	vp[2][3] = depth / 2.0;

	vp[0][0] = w / 2.0;
	vp[1][1] = h / 2.0;
	vp[2][2] = depth / 2.0;
	return vp;
}

/**
	Calculate the look at vector for the current Camera.

	Currently unused and incomplete.

	@param	  eye: The eye of 
	@param centre: y coordinate.
	@param	   up: width of the screen.
	
	@return the viewPort as a Matrix.
*/
MatrixClass lookAt(VectorClass eye, VectorClass centre, VectorClass up)
{
	//std::cout << "lookat" << std::endl;
	VectorClass z = (eye - centre).normalize();
	VectorClass x = (up.crossProd(z)).normalize();
	VectorClass y = (z.crossProd(x)).normalize();

	MatrixClass result = MatrixClass::identity(4);

	for (int i = 0; i < 3; i++)
	{
		result[0][i] = x[i];
		result[1][i] = y[i];
		result[2][i] = z[i];
		result[i][3] = -centre[i];
	}
	//std::cout << "lookat end";
	return result;
}