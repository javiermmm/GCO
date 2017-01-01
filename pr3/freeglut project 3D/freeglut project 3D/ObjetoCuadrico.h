//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef ObjetoCuadrico_H_
#define ObjetoCuadrico_H_

#include "Objeto3D.h"

class ObjetoCuadrico: public Objeto3D {
	protected:
		GLUquadricObj* q;
	public:
		ObjetoCuadrico();
		~ObjetoCuadrico();
		virtual void dibuja() = 0;
};
#endif