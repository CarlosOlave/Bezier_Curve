/*
 *  Camera.h
 *  Theme05_m01
 *
 *  Created by Carlos Olave on 11/13/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

class Camera
{

private:
	float x;
	float y;
	float z;
	
	float fovy;
	
	float radius;	
	float radians;
	float degrees;
	
public:
	
	// Constructor.
	Camera();
	Camera(float _radius,
		   float _y,
		   float _fovy);
	
	// Destructor.
	~Camera();
	
	// Accessors.
	float GetX();
	float GetY();
	float GetZ();
	float GetFovy();
	
	// Setters.
	void RotateCounterClockWise();
	void RotateClockWise();
	void MoveCloserToOrigin();
	void MoveAwayFromOrigin();
};