//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef Escena_H_
#define Escena_H_

#include "ObjetoCompuesto.h"
#include "EsferaCopa.h"

class Escena: public ObjetoCompuesto {
	public:
		Escena();
		~Escena();
		void dibuja();
	private: 
		EsferaCopa** esferasCopas;
};
#endif