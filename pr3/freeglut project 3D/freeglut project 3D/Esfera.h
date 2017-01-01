//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef Esfera_H_
#define Esfera_H_

#include "ObjetoCuadrico.h"

class Esfera: public ObjetoCuadrico {
	protected:
		GLdouble radio;
		int meridianos;
		int paralelos;
	public:
		Esfera();
		Esfera(GLdouble radio, int meridianos, int paralelos);
		~Esfera();
		virtual void dibuja();
};
#endif