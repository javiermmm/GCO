//---------------------------------------------------------------------------
// Javier Martín Moreno-Manzanaro
//---------------------------------------------------------------------------
#ifndef _SEGMENTO_H
#define _SEGMENTO_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
#include "PV2D.h"


class Segmento{
public:
	//Constructores
	Segmento();
	Segmento(PV2D inicio, PV2D vDesp);
	
	//Destructor
	~Segmento();

	//Accedentes y Mutadores
	PV2D getPuntoInicial();
	void setPuntoInicial(PV2D punto);
	PV2D getVectorDesp();
	void setVectorDesp(PV2D v);

	void draw(float r, float g, float b);
	void activa();
	void desactiva();
	bool estaActivado();

private:
	PV2D _puntoInicial;
	PV2D _vectorDesp;
	bool _activo;
};

#endif