/*
 *  Camera.cpp
 *  Theme05_m01
 *
 *  Created by Carlos Olave on 11/13/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "Camera.h"
#include "Utility.h"

Camera::Camera()
{
	radius = 2.0; //20
	degrees = 0.0;
	radians = (degrees*PI)/180;
	x = cos(radians)*radius;
	y = 2.0; //10
	z = sin(radians)*radius;
	fovy = 40;
}

Camera::Camera(float _radius,
			   float _y,
			   float _fovy)
{
	radius = _radius;
	y = _y;
	fovy = _fovy;
	degrees = 0.0;
	radians = (degrees*PI)/180;
	x = cos(radians)*radius;
	z = sin(radians)*radius;
}

Camera::~Camera()
{	
	x = 0.0;
	y = 0.0;
	z = 0.0;
	radius = 0.0;
}

float Camera::GetX()
{
	return x;
}

float Camera::GetY()
{
	return y;
}

float Camera::GetZ()
{
	return z;
}

float Camera::GetFovy()
{
	return fovy;
}

void Camera::RotateCounterClockWise()
{
	degrees += 2;
	if (degrees >= 360)
		degrees = 0.0;
	
	radians = (degrees*PI)/180;
	x = cos(radians)*radius;
	z = sin(radians)*radius;
}

void Camera::RotateClockWise()
{
	degrees -= 2;
	if (degrees <= -360)
		degrees = 0.0;
	
	radians = (degrees*PI)/180;
	x = cos(radians)*radius;
	z = sin(radians)*radius;
}

void Camera::MoveCloserToOrigin()
{
	fovy -= 2;
}

void Camera::MoveAwayFromOrigin()
{
	fovy += 2;
}
