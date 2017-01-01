//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef Coche_H_
#define Coche_H_

#include "ObjetoCompuesto.h"
#include "Rueda.h"
#include "Cubo.h"
#include "Cilindro.h"

class Coche: public ObjetoCompuesto {
	public:
		Coche();
		~Coche();
		void dibuja();
	private: 
		Cubo* chasis;
		Rueda** ruedas;
		Cilindro** faros;
};
#endif