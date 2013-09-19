/*
 *  SceneReader.h
 *  Theme05_m01
 *
 *  Created by Carlos Olave on 11/16/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "Utility.h"
#include "BezierType.h"

class SceneReader
{

private:
	
	BezierType** bezier_objects;
	
	int number_of_bezier_objects;
	
	void SplitLine(const std::string &str_line,
				   char delim,
				   std::vector<std::string> &split_vector);
public:

	// Constructor.
	SceneReader();
	
	// Destructor.
	~SceneReader();
	
	// Read File.
	void ReadFile(const char* file_name);
	
	// Accessors.
	BezierType** GetBezierObjects();
	int GetNumberOfBezierObjects();
};