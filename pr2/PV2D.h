//---------------------------------------------------------------------------
// Javier Martín Moreno-Manzanaro
//---------------------------------------------------------------------------
#ifndef _PV2D_H
#define _PV2D_H

#include <Math.h>

class PV2D{
public:
	//Constructor
	PV2D();
	PV2D(double x, double y);

	PV2D& operator=(const PV2D&);
	
	//Destructor
	~PV2D();

	//Accedentes y Mutadores
	double getX ();
	double getY();
	void setX (double x);
	void setY (double y);

	//operaciones
	double modulo();
	PV2D normaliza();
	PV2D vIzquierda();
	PV2D restaPuntos(PV2D otro);
	double productoEscalar(PV2D otro);
	void multiplicaPorK(float k);

private:
	double _x;
	double _y;
};

#endif