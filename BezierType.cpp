/*
 *  BezierType.cpp
 *  Theme05_m01
 *
 *  Created by Carlos Olave on 11/16/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "BezierType.h"

BezierType::BezierType()
{
}

BezierType::BezierType(BezierEnumType _bezier_type,
					   float** _transform_matrix,
					   const int _U,
					   const int _V)
{
	bezier_type = _bezier_type;
	transform_matrix = _transform_matrix;
	U = _U;
	V = _V;
	int size = (_bezier_type == CURVE? 
				(U+1) :
				(U+1)*(V+1));
	array_of_points = new Point[size];
	array_of_points_size = size;
	array_of_points_index = 0;
	
	min_x = 0.0;
	min_y = 0.0;
	min_z = 0.0;
	max_x = 0.0;
	max_y = 0.0;
	max_z = 0.0;
}

BezierType::~BezierType()
{
	delete array_of_points;
	array_of_points = NULL;
	
	for (int i=0; i<4; i++) 
		delete[] transform_matrix[i];
	delete[] transform_matrix;
}

void BezierType::AddPoint(Point p)
{
	array_of_points[array_of_points_index] = p;
	array_of_points_index++;
}

void BezierType::Print()
{
	// Print object type;
	std::cout << bezier_type << std::endl;
	
	// Print degrees
	std::cout << U << " " << V << std::endl;
	
	// Print transform matrix
	for (int i=0; i<4; i++) {
		for (int j=0; j<4; j++) {
			std::cout << transform_matrix[i][j] << " ";
		}
		std::cout << std::endl;
	}
	
	// Print Control Points
	if (bezier_type == CURVE) {
		for (int i=0; i<array_of_points_size; i++) {
			Point p = array_of_points[i];
			std::cout << p.GetX() << " " << p.GetY() << " " << p.GetZ() << std::endl;
		}
	}
	else if (bezier_type == SURFACE) {
		int count = 0;
		while (count < array_of_points_size) {
			for (int i=0; i<U+1; i++) {
				Point p = array_of_points[count];
				count++;
				std::cout << p.GetX() << " " << p.GetY() << " " << p.GetZ() << " ";
			}
			std::cout << std::endl;
		}
	}
	
}

void BezierType::ApplyDeCasteljauAlgorithm(float t_value)
{
	if (bezier_type == SURFACE)
		ApplySurface(t_value);
	else 
		ApplyCurve(t_value);
}

void BezierType::ApplySurface(float t_value)
{
	// This will hold the collection of rows.
	std::vector<Point>* temp_collection;
	temp_collection = new std::vector<Point>[V+1];
	
	// Contains temporary storage of initial points.
	Point* temp_array = new Point[array_of_points_size];
	int temp_array_size = array_of_points_size;
	for (int i=0; i<temp_array_size; i++) {
		temp_array[i] = array_of_points[i];
	}
	
	// Reset the class collection of points.
	array_of_points = NULL;
	array_of_points_size = 0;
	
	// This will contains a single row.
	array_of_points = new Point[U+1];
	array_of_points_size = U+1;
	
	// Horizontal interpolation. Row points.
	int count = 0;
	int temp_collection_index = 0;
	while (count < temp_array_size) {
		
		for (int i=0; i<U+1; i++) {
			array_of_points[i] = temp_array[count];
			count++;
		}
		
		ApplyCurve(t_value);
		temp_collection[temp_collection_index] = deCastel_curve_points;
		temp_collection_index++;
	}
	
	// Reset the class collection of points.
	array_of_points = NULL;
	array_of_points_size = 0;
	
	// This will contain a single column
	array_of_points = new Point[V+1];
	array_of_points_size = V+1;
	
	// This collection will contain the final interpolated 
	// points and will be use as the source for drawing the surface.
	std::vector<Point>* final_collection;
	final_collection = new std::vector<Point>[temp_collection[0].size()];
	
	// Vertical interpolation - Column points 
	int total_columns = temp_collection[0].size();
	for (int col=0; col<total_columns; col++) {
		for (int row=0; row<V+1; row++) {
			array_of_points[row] = temp_collection[row][col];
		}
		ApplyCurve(t_value);
		final_collection[col] = deCastel_curve_points;
	}
	
	// Set the surface size.
	// The columns <- rows of previous collection.
	// The rows <- columns of previous collections.
	surface_rows = total_columns;
	surface_columns = final_collection[0].size()-1;
	
	deCastel_surface_points = final_collection;

	// Restore the primary array of points.
	array_of_points = temp_array;
	array_of_points_size = temp_array_size;
	
	// Reset temp_array.
	temp_array = NULL;
	temp_array_size = 0;
}

void BezierType::ApplyCurve(float t_value)
{
	Point initial_point = array_of_points[0];
	deCastel_curve_points.clear();
	deCastel_curve_points.push_back(initial_point);
	
	for (float t = 0.0; t<=1.0; t+=t_value) {
		Point final_point;
		DeCasteljauAlgorithm(final_point, t);
		deCastel_curve_points.push_back(final_point);
	}
	deCastel_curve_points.push_back(array_of_points[array_of_points_size-1]);
}

void BezierType::DeCasteljauAlgorithm(Point &FINAL_POINT,
									  const float t)
{
	Point* temp_array = new Point[array_of_points_size];
	for (int i=0; i<array_of_points_size; i++) {
		temp_array[i] = array_of_points[i];
	}
	
	int temp_array_size = array_of_points_size;
	int size = 0;
	while(temp_array_size > 1) {
		size = temp_array_size-1;
		temp_array_size = 0;
		for (int j=0; j<size; j++) {
			Point dest;
			LinearInterpolation(temp_array[j], 
								temp_array[j+1], 
								dest,
								t);
			temp_array[j] = dest;
			temp_array_size++;
		}
	}
	FINAL_POINT = temp_array[0];
}

void BezierType::LinearInterpolation(Point &A,
									 Point &B,
									 Point &AB,
									 const float t)
{
	float x = (float)A.GetX() + (float)(B.GetX()-A.GetX())*t;
	float y = (float)A.GetY() + (float)(B.GetY()-A.GetY())*t;
	float z = (float)A.GetZ() + (float)(B.GetZ()-A.GetZ())*t;
	AB.SetX(x);
	AB.SetY(y);
	AB.SetZ(z);
}

void BezierType::Draw()
{
	if (bezier_type == CURVE) {
		DrawCurve();
	}
	else {
		DrawSurface();
	}

}

void BezierType::DrawSurface()
{
	glPushMatrix();
	
	// Apply the transformation from the .scene file.
	glScalef(transform_matrix[0][0], 
			 transform_matrix[1][1], 
			 transform_matrix[2][2]);
	
	// Since the camera is always looking at the origin
	// we should translate the drawing to the origin.
	glTranslated(-(abs(max_x)-abs(min_x)-.5 + transform_matrix[0][0])/2.0, 
				 -(abs(max_y)-abs(min_y)-.5 + transform_matrix[1][1])/2.0, 
				 -(abs(max_z)-abs(min_z)-.5 + transform_matrix[2][2])/2.0);
	
	
	// draw intial points.
	glColor3f(1.0, 1.0, 1.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for (int col=0; col<surface_columns-1; col++) {
		glBegin(GL_TRIANGLE_STRIP);
		for (int row=0; row<surface_rows-1; row++) {
			Point p1 = deCastel_surface_points[col][row];
			Point p2 = deCastel_surface_points[col+1][row];
			glVertex3f(p1.GetX(), p1.GetY(), p1.GetZ());
			glVertex3f(p2.GetX(), p2.GetY(), p2.GetZ());
		}
		glEnd();
	}
	glFlush();
	glPopMatrix();
	
}

void BezierType::DrawCurve()
{	
	glPushMatrix();
	
	// Apply the transformation from the .scene file.
	glScalef(transform_matrix[0][0], 
			 transform_matrix[1][1], 
			 transform_matrix[2][2]);
	
	// Since the camera is always looking at the origin
	// we should translate the drawing to the origin.
	glTranslated(-(abs(max_x)-abs(min_x)-.5 + transform_matrix[0][0])/2.0, 
				 -(abs(max_y)-abs(min_y)-.5 + transform_matrix[1][1])/2.0, 
				 -(abs(max_z)-abs(min_z)-.5 + transform_matrix[2][2])/2.0);
	
	// Draw the initial points
	glColor3f(0.0, 1.0, 0.0);
	Point base_p1 = array_of_points[0];
	for (int j=1; j<array_of_points_size; j++) {
		Point base_p2 = array_of_points[j];
		DrawLine(base_p1, base_p2);
		base_p1 = base_p2;
	}
		
	int size = deCastel_curve_points.size();
	Point p_init = deCastel_curve_points[0];
	glColor3f(0.0, 0.0, 1.0);
	for (int i=1; i<size; i++) {
		Point p_end = deCastel_curve_points[i];
		DrawLine(p_init, p_end);
		p_init = p_end;
	}
	glPopMatrix();
}


void BezierType::DrawLine(Point &p1,
					      Point &p2)
{
	glBegin(GL_LINES);
	glVertex3f(p1.GetX(), p1.GetY(), p1.GetZ());
	glVertex3f(p2.GetX(), p2.GetY(), p2.GetZ());
	glEnd();
	glFlush();
}

void BezierType::SetMinMaxCoordinates()
{
	float x1, y1, z1;
	float x2, y2, z2;
	
	if (1 < array_of_points_index)
	{
		x1 = array_of_points[0].GetX();
		y1 = array_of_points[0].GetY();
		z1 = array_of_points[0].GetZ();
		
		x2 = array_of_points[1].GetX();
		y2 = array_of_points[1].GetY();
		z2 = array_of_points[1].GetZ();
		
		min_x = std::min(x1, x2);
		max_x = std::max(x1, x2);
		min_y = std::min(y1, y2); 
		max_y = std::max(y1, y2);
		min_z = std::min(z1, z2);
		max_z = std::max(z1, z2);
	}
	
	for (int i=0; i<array_of_points_index; i++) {
		x1 = array_of_points[i].GetX();
		y1 = array_of_points[i].GetY();
		z1 = array_of_points[i].GetZ();
		
		min_x = std::min(x1, min_x);
		max_x = std::max(x1, max_x);
		min_y = std::min(y1, min_y); 
		max_y = std::max(y1, max_y);
		min_z = std::min(z1, min_z);
		max_z = std::max(z1, max_z);
	}
}

float BezierType::GetMaxZ()
{
	return max_z;
}

float BezierType::GetMaxY()
{
	return max_y;
}












