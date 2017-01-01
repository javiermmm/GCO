 

#include "Cubo.h"
#include <math.h>

Cubo::Cubo(){ 	 
    vertice=new PuntoVector3D*[8];
    numeroVertices=8;
    normal=new PuntoVector3D*[6];
    numeroNormales=6;
    cara=new Cara*[6];
    numeroCaras=6;
    vertices();
    caras();
    newelliza();          
	modo=false;
}

void Cubo::vertices() {
    vertice[0]=new PuntoVector3D(0.25f, 0.25f, 0.25f, 1);
    vertice[1]=new PuntoVector3D(0.25f, 0.25f, -0.25f, 1);
    vertice[2]=new PuntoVector3D(-0.25f, 0.25f, -0.25f, 1);
    vertice[3]=new PuntoVector3D(-0.25f, 0.25f, 0.25f, 1);
    vertice[4]=new PuntoVector3D(0.25f, -0.25f, 0.25f, 1);
    vertice[5]=new PuntoVector3D(0.25f, -0.25f, -0.25f, 1);
    vertice[6]=new PuntoVector3D(-0.25f, -0.25f, -0.25f, 1);
    vertice[7]=new PuntoVector3D(-0.25f, -0.25f, 0.25f, 1);
}

void Cubo::caras() {
    VerticeNormal** vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(0,0);
    vn[1]=new VerticeNormal(1,0);
    vn[2]=new VerticeNormal(2,0);
    vn[3]=new VerticeNormal(3,0);
    cara[0]=new Cara(4, vn);
	
	vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(0,1);
    vn[1]=new VerticeNormal(4,1);
    vn[2]=new VerticeNormal(5,1);
    vn[3]=new VerticeNormal(1,1);
    cara[1]=new Cara(4, vn);
	
	vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(4,2);
    vn[1]=new VerticeNormal(7,2);
    vn[2]=new VerticeNormal(6,2);
    vn[3]=new VerticeNormal(5,2);
    cara[2]=new Cara(4, vn);

    vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(3,3);
    vn[1]=new VerticeNormal(2,3);
    vn[2]=new VerticeNormal(6,3);
    vn[3]=new VerticeNormal(7,3);
    cara[3]=new Cara(4, vn);

    vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(0,4);
    vn[1]=new VerticeNormal(3,4);
    vn[2]=new VerticeNormal(7,4);
    vn[3]=new VerticeNormal(4,4);
    cara[4]=new Cara(4, vn);
	
	vn=new VerticeNormal*[4];
    vn[0]=new VerticeNormal(1,5);
    vn[1]=new VerticeNormal(5,5);
    vn[2]=new VerticeNormal(6,5);
    vn[3]=new VerticeNormal(2,5);
    cara[5]=new Cara(4, vn);
}
        