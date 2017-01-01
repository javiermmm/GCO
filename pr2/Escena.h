//---------------------------------------------------------------------------
// Javier Martín Moreno-Manzanaro
//---------------------------------------------------------------------------
#ifndef _Escena_H
#define _Escena_H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <GL/freeglut.h>

#include "PoligonoConvexo.h"
#include "Segmento.h"
#include "Constantes.h"
//---------------------------------------------------------------------------
class Escena{
public:
  Escena();
  ~Escena();
  void iniciar();
  void dibujar(Estado estado);
  GLdouble getXLeft(); 
  GLdouble getXRight();
  GLdouble getYTop();
  GLdouble getYBot();
  void setXLeft(GLdouble xLeft); 
  void setXRight(GLdouble xRight);
  void setYTop(GLdouble yTop);
  void setYBot(GLdouble yBot);
  PoligonoConvexo* getPoligono(int i);
  void setInicioSegmento(PV2D ini);
  PV2D getInicioSegmento();
  PV2D getVectorSegmento();
  void setVectorSegmento(PV2D vDesp);
  void activaSegmento();
  void desactivaSegmento();
  bool segmentoActivado();
  PoligonoConvexo* getPoligonoSeleccionado();
  void setPoligonoSeleccionado(PoligonoConvexo* poligono);
  void creaPelota();
  bool actualiza(int& pasosDados);
private:
	GLdouble _xLeft;
	GLdouble _xRight;
	GLdouble _yBot;
	GLdouble _yTop;
	int _numPoligonos;
	PoligonoConvexo* _poligonos[4];
	PoligonoConvexo* _poligonoSeleccionado;
	PoligonoConvexo* _pelota;
	Segmento* _segmento;
};

#endif
