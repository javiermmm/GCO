//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef Toro_H_
#define Toro_H_

#include "Malla.h"
 
class Toro : public Malla {
	private:             
		void vertices();
        void caras();  
		PuntoVector3D* aplicaMatriz(PuntoVector3D* v, float alfa);
    public:
		Toro();				
};
#endif