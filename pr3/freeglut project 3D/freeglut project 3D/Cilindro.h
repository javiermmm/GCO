//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef Cilindro_H_
#define Cilindro_H_

#include "ObjetoCuadrico.h"

class Cilindro: public ObjetoCuadrico {
	protected:
		GLdouble radioBase;
		GLdouble radioTope;
		GLdouble altura;
		int meridianos;
		int paralelos;
	public:
		Cilindro();
		Cilindro(GLdouble radioBase, GLdouble radioTope, GLdouble altura, int meridianos, int paralelos);
		~Cilindro();
		virtual void dibuja();
};
#endif