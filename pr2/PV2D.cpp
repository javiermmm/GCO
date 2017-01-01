//---------------------------------------------------------------------------
// Javier Martín Moreno-Manzanaro
//---------------------------------------------------------------------------
#include "PV2D.h"

PV2D::PV2D() {}

PV2D::PV2D(double x, double y) : _x(x), _y(y) {}

PV2D& PV2D::operator=(const PV2D& p) { 
	_x = p._x; 
	_y = p._y; 
	return *this; 
}

PV2D::~PV2D() {}

double PV2D::getX() {
	return _x;
}

double PV2D::getY() {
	return _y;
}

void PV2D::setX(double x) {
	_x = x;
}

void PV2D::setY(double y) {
	_y = y;
}

PV2D PV2D::restaPuntos (PV2D otro) {
	return PV2D(_x - otro._x, _y - otro._y);
}

PV2D PV2D::vIzquierda () {
	return PV2D(-_y, _x);
}

double PV2D::productoEscalar(PV2D otro) {
	return ((_x * otro._x) + (_y * otro._y));
}

double PV2D::modulo() {
	return sqrt((_x * _x) + (_y * _y));
}

PV2D PV2D::normaliza() {
	return PV2D(_x/modulo(), _y/modulo());
}

void PV2D::multiplicaPorK(float k)  {
	_x = _x*k;
	_y = _y*k;
}