//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef MallaRevolucion_H_
#define MallaRevolucion_H_

#include "Malla.h"
 
class MallaRevolucion : public Malla {
	private:             
		void vertices();
        void caras();              
    public:
		MallaRevolucion();				
};
#endif
