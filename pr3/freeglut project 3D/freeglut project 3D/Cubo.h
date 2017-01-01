//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef Cubo_H_
#define Cubo_H_

#include "Malla.h"
 
class Cubo : public Malla {
	private:             
		void vertices();
        void caras();              
    public:
		Cubo();				
};
#endif
