//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "Escena.h"

Escena::Escena() {
	//creamos las 10 esferasCopas con un color
	esferasCopas = new EsferaCopa*[10];
	for (int i=0; i<10; i++) {
		if ((0 <= i) && (i <= 3))
			esferasCopas[i] = new EsferaCopa(1.0, 0.0, 0.0);
		else if ((4 <= i) && (i <= 6))
			esferasCopas[i] = new EsferaCopa(0.0, 1.0, 0.0);
		else if ((7 == i) || (i == 8))
			esferasCopas[i] = new EsferaCopa(0.0, 0.0, 1.0);
		else
			esferasCopas[i] = new EsferaCopa(1.0, 1.0, 1.0);
	}

	//Colocamos las esferasCopas
	esferasCopas[1]->traslada(new PuntoVector3D (2.5, 0.0, 0.0, 1));
	esferasCopas[2]->traslada(new PuntoVector3D (5.0, 0.0, 0.0, 1));
	esferasCopas[3]->traslada(new PuntoVector3D (7.5, 0.0, 0.0, 1));
	esferasCopas[4]->traslada(new PuntoVector3D (1.7, 4.0, 0.0, 1));
	esferasCopas[4]->escala(0.9, 0.9, 0.9);
	esferasCopas[5]->traslada(new PuntoVector3D (4.2, 4.0, 0.0, 1));
	esferasCopas[5]->escala(0.9, 0.9, 0.9);
	esferasCopas[6]->traslada(new PuntoVector3D (6.7, 4.0, 0.0, 1));
	esferasCopas[6]->escala(0.9, 0.9, 0.9);
	esferasCopas[7]->traslada(new PuntoVector3D (3.0, 7.5, 0.0, 1));
	esferasCopas[7]->escala(0.8, 0.8, 0.8);
	esferasCopas[8]->traslada(new PuntoVector3D (5.5, 7.5, 0.0, 1));
	esferasCopas[8]->escala(0.8, 0.8, 0.8);
	esferasCopas[9]->traslada(new PuntoVector3D (4.2, 10.5, 0.0, 1));
	esferasCopas[9]->escala(0.7, 0.7, 0.7);
}

Escena::~Escena(){
	for (int i=0; i<10; i++)
		delete esferasCopas[i];

	delete [] esferasCopas;
}

void Escena::dibuja(){
	glMatrixMode(GL_MODELVIEW); //Post-multiplicamos y dibujamos
	glPushMatrix();
		glMultMatrixf(matriz->dameMatrizModelado());
		for (int i=0; i<10; i++) { //Para cada esferaCopa, pedimos su color y la dibujamos
			glColor3f(esferasCopas[i]->getColor()->getR(), esferasCopas[i]->getColor()->getG(), esferasCopas[i]->getColor()->getB());
			esferasCopas[i]->dibuja();
		}
	glPopMatrix();
}