/*
 *  Utility.h
 *  Theme05_m01
 *
 *  Created by Carlos Olave on 11/13/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */
#ifndef UTILITY_H
#define UTILITY_H

#ifdef __APPLE_CC__
#include <GLUT/glut.h>
#else
#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif


#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

#define PI 3.14159265
#define KEY_LOWER_X 'x'
#define KEY_UPPER_X 'X'
#define KEY_LOWER_Z 'z'
#define KEY_UPPER_Z 'Z'
#define KEY_ONE '1'
#define KEY_TWO '2'
#define KEY_THREE '3'
#define KEY_FOUR '4'
#define KEY_FIVE '5'
#define CANNOT_OPEN_SCENE_FILE false

enum BezierEnumType
{
	SURFACE,
	CURVE
};

#endif