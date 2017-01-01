//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef Disco_H_
#define Disco_H_

#include "ObjetoCuadrico.h"

class Disco: public ObjetoCuadrico {
	protected:
		GLdouble radioInterior;
		GLdouble radioExterior;
		int numLados;
		int anillos;
	public:
		Disco();
		Disco(GLdouble radioInterior, GLdouble radioExterior, int numLados, int anillos);
		~Disco();
		virtual void dibuja();
};
#endif