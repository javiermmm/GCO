//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "Esfera.h"

Esfera::Esfera(){}

Esfera::Esfera(GLdouble radio, int meridianos, int paralelos) {
	q = gluNewQuadric();
	this->radio = radio;
	this->meridianos = meridianos;
	this->paralelos = paralelos;
}

Esfera::~Esfera() {
	gluDeleteQuadric(q);
}

void Esfera::dibuja() {
	glMatrixMode(GL_MODELVIEW); //Post-multiplicamos y dibujamos
	glPushMatrix();
		glMultMatrixf(matriz->dameMatrizModelado());
		gluQuadricDrawStyle(q, GLU_FILL);
		gluSphere(q, radio, meridianos, paralelos);
	glPopMatrix();
}