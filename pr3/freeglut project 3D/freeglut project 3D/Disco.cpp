//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "Disco.h"

Disco::Disco() {}

Disco::Disco(GLdouble radioInterior, GLdouble radioExterior, int numLados, int anillos) {
	q = gluNewQuadric();
	this->radioInterior = radioInterior;
	this->radioExterior = radioExterior;
	this->numLados = numLados;
	this->anillos = anillos;
	this->color = new Color(0.5, 0.5, 0.5);
}

Disco::~Disco() {
	gluDeleteQuadric(q);
}

void Disco::dibuja() {
	glMatrixMode(GL_MODELVIEW); //Post-multiplico y dibujo
	glPushMatrix();
		glMultMatrixf(matriz->dameMatrizModelado());
		gluQuadricDrawStyle(q, GLU_FILL);
		glColor3f(this->color->getR(), this->color->getG(), this->color->getB());
		gluDisk(q, radioInterior, radioExterior, numLados, anillos);
	glPopMatrix();
}