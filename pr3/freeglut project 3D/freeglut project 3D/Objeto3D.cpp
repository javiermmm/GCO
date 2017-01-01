//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "Objeto3D.h"

Objeto3D:: Objeto3D() { 	 
    matriz = new TAfin();
	color = new Color();
}

 
Objeto3D:: ~Objeto3D() {
    delete matriz;
}

GLfloat* Objeto3D:: dameMatrizAfin() {
	return matriz->dameMatrizModelado();
}

//To do (usando las correspondientes operaciones de TAfin)
void Objeto3D:: traslada(PuntoVector3D* punto) {
	//To do  [hecho]
	matriz->traslada(punto->getX(), punto->getY(), punto->getZ());
}

void Objeto3D:: escala(GLfloat fX,GLfloat fY,GLfloat fZ) {
	//To do [hecho]
	matriz->escala(fX, fY, fZ);
}

void Objeto3D:: rota(GLfloat alfa,GLfloat fX,GLfloat fY,GLfloat fZ) {
	//To do  [hecho]
	matriz->rota(alfa, fX, fY, fZ);
}

void Objeto3D::setColor(GLfloat r, GLfloat g, GLfloat b) {
	this->color->setR(r);
	this->color->setG(g);
	this->color->setB(b);
}

Color* Objeto3D::getColor() {
	return color;
}