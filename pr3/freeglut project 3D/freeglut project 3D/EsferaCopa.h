//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef EsferaCopa_H_
#define EsferaCopa_H_

#include "ObjetoCompuesto.h"

class EsferaCopa: public ObjetoCompuesto {
	public:
		EsferaCopa();
		EsferaCopa(GLfloat r, GLfloat g, GLfloat b);
		~EsferaCopa();
		void dibuja();
};
#endif