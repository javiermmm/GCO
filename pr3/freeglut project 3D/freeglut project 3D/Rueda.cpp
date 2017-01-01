//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "Rueda.h"
#include "Cilindro.h"
#include "Disco.h"

Rueda::Rueda() {
	//creamos el cilindro y el disco, y movemos este ultimo para que haga de tapa del cilindro
	hijos = new Objeto3D*[2];
	hijos[0] = new Cilindro(2.0, 2.0, 1.0, 20, 30);
	hijos[1] = new Disco(0.01, 2.0, 30, 20);
	hijos[1]->traslada(new PuntoVector3D(0.0, 0.0, 1.0, 1));
}

Rueda::~Rueda() {
	delete hijos[0];
	delete hijos[1];
	delete [] hijos;
}

void Rueda::dibuja() {

	glMatrixMode(GL_MODELVIEW); //Post-multiplicamos y dibujamos
	glPushMatrix();
		glMultMatrixf(matriz->dameMatrizModelado());
		hijos[0]->dibuja();
		hijos[1]->dibuja();
	glPopMatrix();
}