/*
 *  BezierType.h
 *  Theme05_m01
 *
 *  Created by Carlos Olave on 11/16/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "Utility.h"
#include "Point.h"

class BezierType
{

private:
	
	BezierEnumType bezier_type;
	Point* array_of_points;
	std::vector<Point> deCastel_curve_points;
	std::vector<Point>* deCastel_surface_points;
	float** transform_matrix;
	int array_of_points_size;
	int array_of_points_index;
	int surface_columns;
	int surface_rows;
	int U;
	int V;
	int translate_x;
	int translate_y;
	int translate_z;
	float min_x;
	float min_y;
	float min_z;
	float max_x;
	float max_y;
	float max_z;
	
	// Private functions
	void ApplySurface(float t_value);
	void ApplyCurve(float t_value);
	void DeCasteljauAlgorithm(Point &FINAL_POINT,
							  const float t);
	void LinearInterpolation(Point &A,
							 Point &B,
							 Point &AB,
							 const float t);
	void DrawCurve();
	void DrawSurface();
	
public:
	
	// Constructor.
	BezierType();
	BezierType(BezierEnumType _bezier_type,
			   float** _transform_matrix,
			   const int _U,
			   const int _V);
	
	// Destructor.
	~BezierType();
	
	// Modifiers
	void AddPoint(Point p);
	void ApplyDeCasteljauAlgorithm(float t_value);
	void SetMinMaxCoordinates();
	
	// Accessors
	void Print();
	void Draw();
	void DrawLine(Point &p1,
				  Point &p2);
	float GetMaxZ();
	float GetMaxY();

};