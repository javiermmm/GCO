 
#include "Malla.h"
 
Malla::Malla(int nV, int nN, int nC, PuntoVector3D** v, PuntoVector3D** n, Cara** c) {
	numeroVertices=nV;
    vertice=v;
    numeroNormales=nN;
    normal=n;
    numeroCaras=nC;
    cara=c;
    modo=false;
}

Malla::Malla() {}

Malla::~Malla() {
    for (int i=0; i<numeroVertices; i++)
        delete vertice[i];
    delete[] vertice;

    for (int i=0; i<numeroNormales; i++)
        delete normal[i];
    delete[] normal;

    for (int i=0; i<numeroCaras; i++)
        delete cara[i];
    delete[] cara;
}

int Malla::getNumeroVertices() {
    return numeroVertices;
}

int Malla::getNumeroNormales() {
    return numeroNormales;
}

int Malla::getNumeroCaras() {
    return numeroCaras;
}

void Malla::newelliza() {
    for (int i=0; i<numeroCaras; i++) {
	    int v0=cara[i]->getIndiceVerticeK(0);
        int v1=cara[i]->getIndiceVerticeK(1);
        int v2=cara[i]->getIndiceVerticeK(2);
        int v3=cara[i]->getIndiceVerticeK(3);
        PuntoVector3D* v=newell(v0, v1, v2, v3);
        int iN=cara[i]->getIndiceNormalK(0);
        normal[iN]=v;
    }
}

PuntoVector3D* Malla::newell(int i1, int i2, int i3, int i4) {
    PuntoVector3D* v1=vertice[i1];
    PuntoVector3D* v2=vertice[i2];
    PuntoVector3D* v3=vertice[i3];
    PuntoVector3D* v4=vertice[i4];
    GLfloat nx=(v2->getY()-v1->getY())*(v2->getZ()+v1->getZ())+
               (v3->getY()-v2->getY())*(v3->getZ()+v2->getZ())+
               (v4->getY()-v3->getY())*(v4->getZ()+v3->getZ())+
               (v1->getY()-v4->getY())*(v1->getZ()+v4->getZ());
    GLfloat ny=(v2->getZ()-v1->getZ())*(v2->getX()+v1->getX())+
               (v3->getZ()-v2->getZ())*(v3->getX()+v2->getX())+
               (v4->getZ()-v3->getZ())*(v4->getX()+v3->getX())+
               (v1->getZ()-v4->getZ())*(v1->getX()+v4->getX());
    GLfloat nz=(v2->getX()-v1->getX())*(v2->getY()+v1->getY())+
               (v3->getX()-v2->getX())*(v3->getY()+v2->getY())+
               (v4->getX()-v3->getX())*(v4->getY()+v3->getY())+
               (v1->getX()-v4->getX())*(v1->getY()+v4->getY());
    PuntoVector3D* n=new PuntoVector3D(-nx, -ny, -nz, 0);
    n->normalizar();
    return n;
}

void Malla::dibuja() {	 
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		//To do: multiplicar por su atributo de TAfin
		glMultMatrixf(matriz->dameMatrizModelado()); //¿[hecho]?
		for (int i=0; i<numeroCaras; i++) {		
			if (!modo) glBegin(GL_POLYGON);
			else glBegin(GL_LINE_LOOP);
			for (int j=0; j<cara[i]->getNumeroVertices(); j++) {
				int iN=cara[i]->getIndiceNormalK(j);
				int iV=cara[i]->getIndiceVerticeK(j);
				glNormal3f(normal[iN]->getX(), normal[iN]->getY(), normal[iN]->getZ());            				 
				glVertex3f(vertice[iV]->getX(), vertice[iV]->getY(), vertice[iV]->getZ());
			}
			glEnd();
		}
	glPopMatrix();
}

 

