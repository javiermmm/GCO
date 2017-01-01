//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef Prisma_H_
#define Prisma_H_

#include "Malla.h"
 
class Prisma : public Malla {
	private:             
		void vertices();
        void caras();              
    public:
		Prisma();				
};
#endif
