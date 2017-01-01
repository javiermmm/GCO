//---------------------------------------------------------------------------
// Javier Martín Moreno-Manzanaro
//---------------------------------------------------------------------------
#ifndef _POLIGONOCONVEXO_H
#define _POLIGONOCONVEXO_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
#include "PV2D.h"

class PoligonoConvexo{
public:
	//Constructores
	PoligonoConvexo();
	PoligonoConvexo(PV2D C, int N, int r);
	
	//Destructor
	~PoligonoConvexo();

	//Accedentes y Mutadores
	PV2D getVertice (int i);
	PV2D getNormal (int i);
	void setVertice (int i, PV2D p);
	void setNormal (int i, PV2D v);
	void draw(float r, float g, float b);
	bool testPosicionInterior(PV2D punto);
	bool cyrusBeck (PV2D* P, PV2D* v, float& tIn, float& tOut);
	void selecciona();
	void deselecciona();
	bool estaSeleccionado();
	PV2D getCentro();
	void setCentro(PV2D c);
	int getNumLados();
	void setNumLados(int n);
	int getRadio();
	void setRadio (int r);

private:
	PV2D _centro;
	int _numLados;
	int _radio;
	PV2D *_vertices;
	PV2D *_normales;
	bool _seleccionado;
};

#endif