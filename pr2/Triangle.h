//---------------------------------------------------------------------------
// Javier Martín Moreno-Manzanaro
//---------------------------------------------------------------------------
#ifndef _TRIANGLE_H
#define _TRIANGLE_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
#include <iostream>
#include "PV2D.h"
using namespace std;

class Triangle{
public:
	//Constructor
	Triangle(PV2D p1, PV2D p2, PV2D p3);
	
	//Destructor
	~Triangle();

	//Accedentes y Mutadores
	PV2D getVertice (int i);
	void setVertice (int i, PV2D p);
	void draw(float r, float g, float b);
	bool testPosicion (PV2D punto, GLdouble xLeft, GLdouble xRight, GLdouble yTop, GLdouble yBot, 
				   int HEIGHT, int WIDTH);

private:
	PV2D _vertices[3];
};

#endif