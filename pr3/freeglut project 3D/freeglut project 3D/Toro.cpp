//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "Toro.h"
#include "Constantes.h"
#include <math.h>

Toro::Toro(){ 	 
	//numero de vertices = numero de perfiles * numero de puntos que tiene un perfil
	//el numero de caras y normales, no es unos menos (como en las otras mallas), porque el toro es circular
	//y los ultimos vertices se uniran con los primeros
    vertice=new PuntoVector3D*[numPerfiles*nPerfil];
    numeroVertices=numPerfiles*nPerfil;
    normal=new PuntoVector3D*[numPerfiles*nPerfil];
    numeroNormales=numPerfiles*nPerfil;
    cara=new Cara*[numPerfiles*nPerfil];
    numeroCaras=numPerfiles*nPerfil;
    vertices();
    caras();
    newelliza();
	modo=true;
}

PuntoVector3D* Toro::aplicaMatriz(PuntoVector3D* v, float alfa) {
	float R = 0.60; //Radio del Toro
	float m[16]; //Construyo la matriz del Marco de Frenet
	m[0] = cos(alfa);	m[4] = 0;	m[8] = -sin(alfa);	m[12] = R*cos(alfa);
	m[1] = 0;			m[5] = -1;	m[9] = 0;			m[13] = 0;
	m[2] = sin(alfa);	m[6] = 0;	m[10] = cos(alfa);	m[14] = R*sin(alfa);
	m[3] = 0;			m[7] = 0;	m[11] = 0;			m[15] = 1;

	//Multiplico el punto del perfil por la matriz (teniendo en cuenta el angulo), para ir sacando los puntos del Toro
	GLfloat x = m[0]*v->getX() + m[4]*v->getY() + m[8]*v->getZ() + m[12];
	GLfloat y = m[1]*v->getX() + m[5]*v->getY() + m[9]*v->getZ() + m[13];
	GLfloat z = m[2]*v->getX() + m[6]*v->getY() + m[10]*v->getZ() + m[14];

	return new PuntoVector3D (x, y, z, 1);
}

void Toro::vertices() {
	
	float inc = (2*PI/nPerfil);
	float r = 0.2f;

	//Creamos un perfil de nPerfil puntos
	PuntoVector3D* perfil[nPerfil];
	for (int i=0; i<nPerfil; i++){
		perfil[i]=new PuntoVector3D(r * cos(2*PI-i*inc) , r * sin(2*PI-i*inc), 0, 1);
	}

	//Calculo el incremento del angulo de cada perfil
	float alfa = (2*PI/numPerfiles);
	float ang = 0;
	int v = 0;
	for (int i=0; i<numPerfiles; i++){ //para cada perfil...
		ang += alfa;
		for (int j=0; j<nPerfil; j++) { //para cada punto del perfil...
			vertice[v] = aplicaMatriz (perfil[j], ang); //Multiplico el punto por la matriz
			v++;
		}
	}
}

void Toro::caras() {
	int numC = 0;
	for (int i = 0; i<numPerfiles; i++){ //Para cada perfil...
		for (int j=0; j<nPerfil; j++) { //Para cada punto del perfil...
			VerticeNormal** vn=new VerticeNormal*[4];
			if (j != nPerfil-1) { //Si no estoy en la cara cuyo primer vertice es el ultimo del perfil...
				//Las caras están creadas igual que en la copa, con la salvedad del modulo con el numero de vertices
				//por ser una malla circular
				vn[0]=new VerticeNormal(numC % numeroVertices,numC);
				vn[1]=new VerticeNormal((numC+nPerfil) % numeroVertices,numC);
				vn[2]=new VerticeNormal((numC+1+nPerfil) % numeroVertices,numC);
				vn[3]=new VerticeNormal((numC+1) % numeroVertices,numC);
				cara[numC]=new Cara(4, vn);
				numC++;
			}
			else {
				//Las caras están creadas igual que en la copa, con la salvedad del modulo con el numero de vertices
				//por ser una malla circular
				vn[0]=new VerticeNormal(numC % numeroVertices,numC);
				vn[1]=new VerticeNormal((numC+nPerfil) % numeroVertices,numC);
				vn[2]=new VerticeNormal((numC+1) % numeroVertices,numC);
				vn[3]=new VerticeNormal((numC+1-nPerfil) % numeroVertices,numC);
				cara[numC]=new Cara(4, vn);
				numC++;
			}
		}
	}
}
        