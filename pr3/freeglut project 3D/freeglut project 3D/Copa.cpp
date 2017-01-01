//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "Copa.h"
#include "Constantes.h"
#include <math.h>

Copa::Copa(){ 	 
	//33 niveles de circunferencias. La base de la copa, la base del palo, el tope del palo y los 30 del cuenco de la copa
    vertice=new PuntoVector3D*[33*nP];
    numeroVertices=33*nP;
    normal=new PuntoVector3D*[32*nP];
    numeroNormales=32*nP;
    cara=new Cara*[32*nP];
    numeroCaras=32*nP;
    vertices();
    caras();
    newelliza();
	modo=true;
}

void Copa::vertices() {
	
	float inc = (2*PI/nP);
	int v = 0;
	float r = 0.15f;
	float altura = 0.00f;

	//Base de la copa
	for (int i=0; i<nP; i++){
		vertice[v]=new PuntoVector3D(r * cos(2*PI-i*inc) , altura, r * sin(2*PI-i*inc), 1); //creamos los vertices de una circunferencia
		v++;
	}

	//Base del palo
	r = 0.02f;
	altura = 0.05f;
	for (int i=0; i<nP; i++) {
		vertice[v]=new PuntoVector3D(r * cos(2*PI-i*inc), altura, r * sin(2*PI-i*inc),1); //creamos los vertices de una circunferencia
		v++;
	}
	
	//Tope del palo
	altura = 0.20f;
	for (int i=0; i<nP; i++) {
		vertice[v]=new PuntoVector3D(r * cos(2*PI-i*inc), altura, r * sin(2*PI-i*inc),1); //creamos los vertices de una circunferencia
		v++;
	}
	
	//Cuenco
	for (int j=0; j<30; j++) {
		r += 0.005;
		//la altura podria incrementarse en una cantidad fija para que la copa saliera recta como una copa de martini
		//pongo altura += (r*r), para que la forma del cuenco de la copa sea redondeado siguiendo la curva y = x^2
		altura += (r*r); 
		for (int i=0; i<nP; i++) {
			vertice[v]=new PuntoVector3D(r * cos(2*PI-i*inc), altura, r * sin(2*PI-i*inc),1); //creamos los vertices de una circunferencia
			v++;
		}
	}
}

void Copa::caras() {
	int numC = 0;
	
	for (int i = 0; i<32; i++){ //Para cada nivel de circunferencia...
		for (int j=0; j<nP; j++) { //Para cada punto de la circunferencia de un nivel
			VerticeNormal** vn=new VerticeNormal*[4];
			if (j != nP-1) { // Si no es la cara que empieza por el ultimo vertice...
				vn[0]=new VerticeNormal(numC,numC);
				vn[1]=new VerticeNormal(numC+nP,numC);
				vn[2]=new VerticeNormal(numC+1+nP,numC);
				vn[3]=new VerticeNormal(numC+1,numC);
				cara[numC]=new Cara(4, vn);
				numC++;
			}
			else {
				vn[0]=new VerticeNormal(numC,numC);
				vn[1]=new VerticeNormal(numC+nP,numC);
				vn[2]=new VerticeNormal(numC+1,numC);
				vn[3]=new VerticeNormal(numC+1-nP,numC);
				cara[numC]=new Cara(4, vn);
				numC++;
			}
		}
	}
}
        