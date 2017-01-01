//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "ObjetoCompuesto.h"

ObjetoCompuesto:: ObjetoCompuesto() {
	hijos = new Objeto3D*[1000000];
	numHijos = 0;
}

ObjetoCompuesto:: ~ObjetoCompuesto() {
	for(int i =0; i < numHijos; i++) {     
		delete hijos[i];
    }  
}

void ObjetoCompuesto:: dibuja() {
	//To do [hecho]
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(matriz->dameMatrizModelado());
	for(int i=0; i<numHijos; i++)
		hijos[i]->dibuja();
	glPopMatrix();
}

void ObjetoCompuesto:: introduceObjeto(Objeto3D* objeto) {
	//To do [hecho]
	hijos[numHijos] = objeto;
	numHijos++;
}




