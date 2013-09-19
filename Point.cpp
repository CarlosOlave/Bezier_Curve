/*
 *  Point.cpp
 *  Theme05_m01
 *
 *  Created by Carlos Olave on 11/16/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "Point.h"

Point::Point()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

Point::Point(float _x,
			 float _y,
			 float _z)
{
	x = _x;
	y = _y;
	z = _z;
}

Point::~Point()
{
	x = 0.0;
	y = 0.0;
	z = 0.0;
}

float Point::GetX()
{
	return x;
}

float Point::GetY()
{
	return y;
}

float Point::GetZ()
{
	return z;
}

void Point::SetX(float _x)
{
	x = _x;
}

void Point::SetY(float _y)
{
	y = _y;
}

void Point::SetZ(float _z)
{
	z = _z;
}