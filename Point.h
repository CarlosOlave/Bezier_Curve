/*
 *  Point.h
 *  Theme05_m01
 *
 *  Created by Carlos Olave on 11/16/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

class Point
{

private:
	float x;
	float y;
	float z;
	
public:
	
	// Constructors.
	Point();
	Point(float _x,
		  float _y,
		  float _z);
	
	// Destructor.
	~Point();
	
	// Accessors
	float GetX();
	float GetY();
	float GetZ();
	
	// Modifiers
	void SetX(float _x);
	void SetY(float _y);
	void SetZ(float _z);
};
