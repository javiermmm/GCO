//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "EsferaCopa.h"
#include "Esfera.h"
#include "Copa.h"

EsferaCopa::EsferaCopa(){}

EsferaCopa::EsferaCopa(GLfloat r, GLfloat g, GLfloat b) {
	//Creamos la Copa y la escalamos
	hijos = new Objeto3D*[2];
	hijos[0] = new Copa();
	hijos[0]->escala(6.0, 6.0, 6.0);
	//Creamos la esfera, la escalamos y la colocamos en el cuenco de la copa
	hijos[1] = new Esfera(1, 20, 30);
	hijos[1]->traslada(new PuntoVector3D (0.0, 2.5, 0.0, 1));
	hijos[1]->escala(0.5, 0.5, 0.5);
	//ponemos color a la EsferaCopa
	this->color = new Color (r, g, b);
}

EsferaCopa::~EsferaCopa() {

}

void EsferaCopa::dibuja() {

	glMatrixMode(GL_MODELVIEW); //Post-multiplicamos y dibujamos
	glPushMatrix();
		glMultMatrixf(matriz->dameMatrizModelado());
		hijos[0]->dibuja();
		hijos[1]->dibuja();
	glPopMatrix();
}