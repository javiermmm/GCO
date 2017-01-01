//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "MallaRevolucion.h"
#include "Constantes.h"
#include <math.h>

MallaRevolucion::MallaRevolucion(){ 
	//el numero de vertices es 5 puntos por cada muestra, donde el numero de muestras es N
    vertice=new PuntoVector3D*[5*N];
    numeroVertices=5*N;
    normal=new PuntoVector3D*[4*N];
    numeroNormales=4*N;
    cara=new Cara*[4*N];
    numeroCaras=4*N;
    vertices();
    caras();
    newelliza();
	modo=false;
}

void MallaRevolucion::vertices() {
	
	//Calculo el incremento del angulo que le corresponde a cad gajo de la malla
	float alfa = (2*PI/N);
	float ang = alfa;
	int v = 0;
	for (int i=0; i<N; i++) {
		ang = alfa*i;
		//introducimos los vertices, calculándolos por "columnas", es decir, por perfiles
		vertice[v] = new PuntoVector3D(0.10f * cos(ang), 0.00f, 0.10f * sin(ang),1);
		v++;
		vertice[v] = new PuntoVector3D(0.10f * cos(ang), 0.10f, 0.10f * sin(ang),1);
		v++;
		vertice[v] = new PuntoVector3D(0.30f * cos(ang), 0.30f, 0.30f * sin(ang),1);
		v++;
		vertice[v] = new PuntoVector3D(0.30f * cos(ang), 0.60f, 0.30f * sin(ang),1);
		v++;
		vertice[v] = new PuntoVector3D(0.10f * cos(ang), 0.80f, 0.10f * sin(ang),1);
		v++;
	}
	
}

void MallaRevolucion::caras() {
	//Defino las caras del primer gajo, a mano

    VerticeNormal** vn=new VerticeNormal*[4];

	//SECTOR CILINDRICO DE MAS ABAJO (SECTOR 0)
    vn[0]=new VerticeNormal(0,0);
    vn[1]=new VerticeNormal(5,0);
    vn[2]=new VerticeNormal(6,0);
    vn[3]=new VerticeNormal(1,0);
    cara[0]=new Cara(4, vn);
	
	//SECTOR CÓNICO DE MAS ABAJO(SECTOR 1)
	vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(1,1);
    vn[1]=new VerticeNormal(6,1);
    vn[2]=new VerticeNormal(7,1);
    vn[3]=new VerticeNormal(2,1);
    cara[1]=new Cara(4, vn);

	//SECTOR CILINDRICO DE MAS ARRIBA(SECTOR 2)
	vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(2,2);
    vn[1]=new VerticeNormal(7,2);
    vn[2]=new VerticeNormal(8,2);
    vn[3]=new VerticeNormal(3,2);
    cara[2]=new Cara(4, vn);

	//SECTOR CÓNICO DE MAS ARRIBA(SECTOR 3)
	vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(3,3);
    vn[1]=new VerticeNormal(8,3);
    vn[2]=new VerticeNormal(9,3);
    vn[3]=new VerticeNormal(4,3);
    cara[3]=new Cara(4, vn);

	for (int i=4; i<numeroCaras; i++) { //el resto de caras se formaran sumando 5 a los vertices de hace 4 caras
		vn=new VerticeNormal*[4];
		vn[0]=new VerticeNormal((cara[i-4]->getIndiceVerticeK(0) + 5) % numeroVertices,i);
		vn[1]=new VerticeNormal((cara[i-4]->getIndiceVerticeK(1) + 5) % numeroVertices,i);
		vn[2]=new VerticeNormal((cara[i-4]->getIndiceVerticeK(2) + 5) % numeroVertices,i);
		vn[3]=new VerticeNormal((cara[i-4]->getIndiceVerticeK(3) + 5) % numeroVertices,i);
		cara[i]=new Cara(4, vn);
	}

}
        