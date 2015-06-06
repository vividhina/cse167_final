#include "Camera.h"

Camera::Camera()
{
    c.identity();
    e.set(25.0, 10.0, 40.0);
    d.set(0.0, 0.0, 0.0);
    up.set(0.0, 1.0, 0.0);
    
    //Pre-define a camera matrix (and its inverse) that are shifted 'e' from the origin
    //This is used as a default camera position for Project 1
    //c.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, e[0], e[1], e[2], 1);
    //ci.set(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, -e[0], -e[1], -e[2], 1);
}

Camera::~Camera()
{
    //Delete and dynamically allocated memory/objects here
}

Matrix4& Camera::getMatrix()
{
    return c;
}

Matrix4& Camera::getInverseMatrix()
{
    return ci;
}

void Camera::update()
{
    //Update the Camera Matrix using d, e, and up
    //Solve for the z, x, and y axes of the camera matrix
    //Use these axes and the e vector to create a camera matrix c
    //Use c to solve for an inverse camera matrix ci
	Vector3 z, x, y;
	Matrix4 c, ci, R, T;
	z = (e - d) * (1 / (e - d).magnitude());
	x = up.cross(z) * (1 / up.cross(z).magnitude());
	y = z.cross(x);
	R.set(x.m[0], y.m[0], z.m[0], 0,
		  x.m[1], y.m[1], z.m[1], 0,
		  x.m[2], y.m[2], z.m[2], 0,
		  0, 0, 0, 1);

	T.set(1, 0, 0, 0,
		  0, 1, 0, 0,
		  0, 0, 1, 0,
		  -e.m[0], -e.m[1], -e.m[2], 1);
	c.set(x.m[0], y.m[0], z.m[0], e.m[0],
		  x.m[1], y.m[1], z.m[1], e.m[1],
		  x.m[2], y.m[2], z.m[2], e.m[2],
		  0, 0, 0, 1);
	c.transpose();
	//R.print("");
	//T.print("");
	this->ci = R*T;
	//ci.print("");
}

void Camera::set(Vector3& e, Vector3& d, Vector3& up)
{
    this->e = e;
    this->d = d;
    this->up = up;
    update();
}
