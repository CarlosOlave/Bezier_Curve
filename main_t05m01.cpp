/*
 *  main_t05m01.cpp
 *  Theme05_m01
 *
 *  Created by Carlos Olave on 11/13/11.
 *  Copyright 2011 Columbia University. All rights reserved.
 *
 */

#include "Camera.h"
#include "SceneReader.h"

// Global variable.
Camera displayCamera;
SceneReader sceneReader;
BezierType** bezier_type;
int bezier_type_size;
int print_index;
GLint width, height;
float t_value;

// Light Color.
GLfloat WHITE[] = {1, 1, 1};
GLfloat RED[] = {1, 0, 0 };

void GenerateList()
{
	glEnable(GL_COLOR_MATERIAL);
	for (int i=0; i<bezier_type_size; i++)
		bezier_type[i]->ApplyDeCasteljauAlgorithm((float)t_value);
}

void init()
{
	// 1st light source.
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, WHITE);
	glLightfv(GL_LIGHT0, GL_SPECULAR, WHITE);
	glMaterialfv(GL_FRONT, GL_SPECULAR, WHITE);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	
	// 2nd light source.
	glEnable(GL_DEPTH_TEST);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, RED);
	glLightfv(GL_LIGHT1, GL_SPECULAR, RED);
	glMaterialfv(GL_FRONT, GL_SPECULAR, RED);
	glMaterialf(GL_FRONT, GL_SHININESS, 30);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);
	
	// Default value
	t_value = 1.0;
	
	// Generates primitives.
	GenerateList();
}

void display()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(displayCamera.GetFovy(), GLfloat(width)/GLfloat(height), 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	
	glPushMatrix();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();	
	glPushMatrix();
	gluLookAt(displayCamera.GetX(), displayCamera.GetY(), displayCamera.GetZ(), 
			  0, 0, 0, 
			  0, 1, 0);
	if (print_index < 0) {
		for (int i=0; i<bezier_type_size; i++)
			bezier_type[i]->Draw();
	}	
	else {
		bezier_type[print_index]->Draw();
	}

	glutSwapBuffers();
	glPopMatrix();
	glPopMatrix();
}

void reshape(GLint w, GLint h)
{
	width = w;
	height = h;
	
	glViewport(0, 0, w, h);
	glPushMatrix();
	glLoadIdentity();	
	
	// First light source.
	GLfloat light0_position[] = {-30, 30, 20, 1};
	glLightfv(GL_LIGHT0, GL_POSITION, light0_position);
	
	// Second light source.
	GLfloat light1_position[] = {40, 30, 20, 1};
	glLightfv(GL_LIGHT1, GL_POSITION, light1_position);
	
	glPopMatrix();
}

void special(int key, int, int)
{
	switch (key) {
		case GLUT_KEY_LEFT:
			displayCamera.RotateCounterClockWise();
			break;
		case GLUT_KEY_RIGHT:
			displayCamera.RotateClockWise();
			break;
		case GLUT_KEY_UP:
			print_index = (print_index == bezier_type_size-1?
						   -1 : print_index+=1);
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void processNormalKeys(unsigned char key, int x, int y) 
{
	
	switch (key) {
		case KEY_LOWER_X:
			displayCamera.MoveAwayFromOrigin();
			break;
		case KEY_UPPER_X:
			displayCamera.MoveAwayFromOrigin();
			break;
		case KEY_LOWER_Z:
			displayCamera.MoveCloserToOrigin();
			break;
		case KEY_UPPER_Z:
			displayCamera.MoveCloserToOrigin();
			break;
		case KEY_ONE:
			t_value = 1.00;
			GenerateList();
			break;
		case KEY_TWO:
			t_value = 0.33;
			GenerateList();
			break;
		case KEY_THREE:
			t_value = 0.11;
			GenerateList();
			break;
		case KEY_FOUR:
			t_value = 0.0370;
			GenerateList();
			break;
		case KEY_FIVE:
			t_value = 0.0123;
			GenerateList();
			break;
		default:
			break;
	}
	glutPostRedisplay();
}

void SetSceneCamera()
{
	BezierType** bezierTemp = sceneReader.GetBezierObjects();
	int size = sceneReader.GetNumberOfBezierObjects();
	float radius = 0.0;
	float y = 0.0;
	
	for (int i=0; i<size; i++) {
		BezierType* bt = bezierTemp[i];
		radius = std::max(bt->GetMaxZ(), radius);
		y = std::max(bt->GetMaxY(), y);
	}	
	
	displayCamera = Camera(radius,
						   y,
						   70.0);
}

int main (int argc, char** argv)
{	
	glutInit(&argc, argv);

	if (argc == 1) {
		std::cout << "No file specify." << std::endl;
		return 0;
	}
	
	if (argc > 1) {
		std::string file = argv[1];
		if (file.find(".scene") == std::string::npos)
		{
			std::cout << "Wrong file format." << std::endl;
			return 0;
		}
		else {
			sceneReader.ReadFile(argv[1]);
			bezier_type = sceneReader.GetBezierObjects();
			bezier_type_size = sceneReader.GetNumberOfBezierObjects();
			print_index = -1;
			SetSceneCamera();
		}
	}
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowPosition(80, 80);
	glutInitWindowSize(800, 600);
	glutCreateWindow("main_t05m01");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special);
	glutKeyboardFunc(processNormalKeys);
	init();
	glutMainLoop();
	
	return 0;
}

