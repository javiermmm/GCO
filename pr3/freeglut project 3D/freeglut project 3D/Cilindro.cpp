//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "Cilindro.h"

Cilindro::Cilindro() {}

Cilindro::Cilindro(GLdouble radioBase, GLdouble radioTope, GLdouble altura, int meridianos, int paralelos) {
	q = gluNewQuadric();
	this->radioBase = radioBase;
	this->radioTope = radioTope;
	this->altura = altura;
	this->meridianos = meridianos;
	this->paralelos = paralelos;
	this->color = new Color(0.0, 0.0, 0.0);
}

Cilindro::~Cilindro() {
	gluDeleteQuadric(q);
}

void Cilindro::dibuja() {
	glMatrixMode(GL_MODELVIEW); //Post-multiplicamos y luego dibujamos
	glPushMatrix(); 
		glMultMatrixf(matriz->dameMatrizModelado());
		gluQuadricDrawStyle(q, GLU_FILL);
		glColor3f(this->color->getR(), this->color->getG(), this->color->getB());
		gluCylinder(q, radioBase, radioTope, altura, meridianos, paralelos);
	glPopMatrix();
}