//===========================================
// Javier Martin Moreno-Manzanaro
//=========================================== 

#include "Prisma.h"
#include "Constantes.h"
#include <math.h>

Prisma::Prisma(){ 	 
	//14 vertices. 7 de la cara de arriba y 7 de la de abajo
    vertice=new PuntoVector3D*[14];
    numeroVertices=14;
    normal=new PuntoVector3D*[9];
    numeroNormales=9;
    cara=new Cara*[9];
    numeroCaras=9;
    vertices();
    caras();
    newelliza();

	//Colocamos las normales de la base y la tapa a mano.
	//BASE
	PuntoVector3D* nBase = new PuntoVector3D(0.0, -1.0, -0.0, 0);
    int iNBase=cara[0]->getIndiceNormalK(0);
    normal[iNBase]=nBase;

	//TAPA
	PuntoVector3D* nTapa = new PuntoVector3D(0.0, 1.0, -0.0, 0);
    int iNTapa=cara[1]->getIndiceNormalK(0);
    normal[iNTapa]=nTapa;

	modo=false;
}

void Prisma::vertices() {
	//BASE
    vertice[0]=new PuntoVector3D(0.10f, 0.00f, 0.10f, 1);
    vertice[1]=new PuntoVector3D(0.50f, 0.00f, 0.10f, 1);
    vertice[2]=new PuntoVector3D(0.35f, 0.00f, 0.25f, 1);
    vertice[3]=new PuntoVector3D(0.65f, 0.00f, 0.55f, 1);
    vertice[4]=new PuntoVector3D(0.55f, 0.00f, 0.65f, 1);
    vertice[5]=new PuntoVector3D(0.25f, 0.00f, 0.35f, 1);
    vertice[6]=new PuntoVector3D(0.10f, 0.00f, 0.50f, 1);

	//TAPA
    vertice[7]= new PuntoVector3D(0.10f, H, 0.10f, 1);
    vertice[8]= new PuntoVector3D(0.50f, H, 0.10f, 1);
    vertice[9]= new PuntoVector3D(0.35f, H, 0.25f, 1);
    vertice[10]=new PuntoVector3D(0.65f, H, 0.55f, 1);
    vertice[11]=new PuntoVector3D(0.55f, H, 0.65f, 1);
    vertice[12]=new PuntoVector3D(0.25f, H, 0.35f, 1);
    vertice[13]=new PuntoVector3D(0.10f, H, 0.50f, 1);
}

void Prisma::caras() {

	VerticeNormal** vn=new VerticeNormal*[7];
	//CARAS DEL POLIGONO (LA FLECHA)
	//(BASE)
	vn=new VerticeNormal*[7];
    vn[0]=new VerticeNormal(0,0);
    vn[1]=new VerticeNormal(6,0);
    vn[2]=new VerticeNormal(5,0);
    vn[3]=new VerticeNormal(4,0);
	vn[4]=new VerticeNormal(3,0);
	vn[5]=new VerticeNormal(2,0);
	vn[6]=new VerticeNormal(1,0);
    cara[0]=new Cara(7, vn);

	//(TAPA)
	vn=new VerticeNormal*[7];
    vn[0]=new VerticeNormal(7,1);
    vn[1]=new VerticeNormal(8,1);
    vn[2]=new VerticeNormal(9,1);
    vn[3]=new VerticeNormal(10,1);
	vn[4]=new VerticeNormal(11,1);
	vn[5]=new VerticeNormal(12,1);
	vn[6]=new VerticeNormal(13,1);
    cara[1]=new Cara(7, vn);

	//CARAS CUADRANGULARES (LATERALES)
    vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(0,2);
    vn[1]=new VerticeNormal(1,2);
    vn[2]=new VerticeNormal(8,2);
    vn[3]=new VerticeNormal(7,2);
    cara[2]=new Cara(4, vn);
	
	vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(1,3);
    vn[1]=new VerticeNormal(2,3);
    vn[2]=new VerticeNormal(9,3);
    vn[3]=new VerticeNormal(8,3);
    cara[3]=new Cara(4, vn);
	
	vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(2,4);
    vn[1]=new VerticeNormal(3,4);
    vn[2]=new VerticeNormal(10,4);
    vn[3]=new VerticeNormal(9,4);
    cara[4]=new Cara(4, vn);

    vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(3,5);
    vn[1]=new VerticeNormal(4,5);
    vn[2]=new VerticeNormal(11,5);
    vn[3]=new VerticeNormal(10,5);
    cara[5]=new Cara(4, vn);

    vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(4,6);
    vn[1]=new VerticeNormal(5,6);
    vn[2]=new VerticeNormal(12,6);
    vn[3]=new VerticeNormal(11,6);
    cara[6]=new Cara(4, vn);
	
	vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(5,7);
    vn[1]=new VerticeNormal(6,7);
    vn[2]=new VerticeNormal(13,7);
    vn[3]=new VerticeNormal(12,7);
    cara[7]=new Cara(4, vn);

	vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(6,8);
    vn[1]=new VerticeNormal(0,8);
    vn[2]=new VerticeNormal(7,8);
    vn[3]=new VerticeNormal(13,8);
    cara[8]=new Cara(4, vn);
}
        