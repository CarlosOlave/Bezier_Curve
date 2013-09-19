/*
 *  SceneReader.cpp
 *  Theme05_m01
 *
 *  Created by Carlos Olave on 11/16/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "SceneReader.h"

SceneReader::SceneReader()
{

}

SceneReader::~SceneReader()
{

}

void SceneReader::ReadFile(const char* file_name)
{
	// Attempt to open file.
	std::string str_line = "";
	std::ifstream isSceneFile(file_name);

	// If file cannot be open then return.
	if (isSceneFile.is_open() == CANNOT_OPEN_SCENE_FILE)
	{
		std::cout << "Failed to open .scene file" << std::endl;
		return;
	}
	
	//BezierType** bezier_objects;
	std::vector<std::string> vector_split;
	int bezier_collection_index;
	
	while (!isSceneFile.eof()) {
		
		// Read line by line.
		getline(isSceneFile, str_line);
	
		SplitLine(str_line,
				  ' ',
				  vector_split);
		
		// First line states the number of curves 
		// and/or surfaces in the file
		if (vector_split.size() == 1)
		{
			number_of_bezier_objects = ::atoi(vector_split[0].c_str());
			bezier_objects = new BezierType*[number_of_bezier_objects];
			bezier_collection_index = 0;
		}
		else if (vector_split.size() == 2)
		{
			// Line with two integers (“u_deg” and “v_deg”) 
			// specifying the degree of the curve/surface in U 
			// and V (note: for a curve, the V will always be “0”)
			int U = ::atoi(vector_split[0].c_str());
			int V = ::atoi(vector_split[1].c_str());
			
			// Clear vector container.
			vector_split.clear();
			
			// Read the next four lines - 4 lines of 4 floats each, 
			// specifying the modeling transform that should be 
			// applied to this curve/surface
			float** transform_matrix = new float*[4];
			for (int i=0; i<4; i++) transform_matrix[i] = new float[4];
		
			for (int i=0; i<4; i++) {
				getline(isSceneFile, str_line);
				SplitLine(str_line,
						  ' ',
						  vector_split);
				for (int j=0; j<4; j++) {
					transform_matrix[i][j] = ::atof(vector_split[j].c_str());
				}
				vector_split.clear();
			}
			
			// Create a Bezier object.
			BezierType* bezier_type;
			BezierEnumType bezier_enum_type = (V == 0? CURVE : SURFACE);
			bezier_type = new BezierType(bezier_enum_type,
										 transform_matrix,
										 U,
										 V);
			
			// Clear out transform_matrix
			//for (int i=0; i<4; i++) delete[] transform_matrix[i];
			//delete transform_matrix;
			
			// Now we are ready to read the control points
			
			// For a curve, there will be (u_deg+1) lines, 
			// with one XYZ point per line
			if (bezier_enum_type == CURVE) {
			
				for (int i=0; i<U+1; i++) {
					getline(isSceneFile, str_line);
					SplitLine(str_line,
							  ' ',
							  vector_split);
					Point p = Point(::atof(vector_split[0].c_str()),
									::atof(vector_split[1].c_str()),
									::atof(vector_split[2].c_str()));
					
					bezier_type->AddPoint(p);
					
					vector_split.clear();
				}
				
			}
			else if (bezier_enum_type == SURFACE) {
				
				for (int i=0; i<V+1; i++) {
					getline(isSceneFile, str_line);
					SplitLine(str_line,
							  ' ',
							  vector_split);
					for (int c=0; c<U+1; c++) {
						Point p = Point(::atof(vector_split[0].c_str()),
										::atof(vector_split[1].c_str()),
										::atof(vector_split[2].c_str()));
						bezier_type->AddPoint(p);
						vector_split.erase(vector_split.begin());
						vector_split.erase(vector_split.begin());
						vector_split.erase(vector_split.begin());
					}
					
					vector_split.clear();
				}
			}
			bezier_type->SetMinMaxCoordinates();
			bezier_objects[bezier_collection_index] = bezier_type;
			bezier_collection_index++;
			
		
		}
		
		vector_split.clear();
	}
}


void SceneReader::SplitLine(const std::string &str_line,
							char delim,
							std::vector<std::string> &split_vector)
{
	std::stringstream ss(str_line);
	std::string str_token = "";
	while (std::getline(ss, str_token, delim)){
		if (str_token != "")
			split_vector.push_back(str_token);
	}
}


BezierType** SceneReader::GetBezierObjects()
{
	return bezier_objects;
}

int SceneReader::GetNumberOfBezierObjects()
{
	return number_of_bezier_objects;
}
							