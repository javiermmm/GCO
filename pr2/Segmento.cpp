//---------------------------------------------------------------------------
// Javier Martín Moreno-Manzanaro
//---------------------------------------------------------------------------

#include "Segmento.h"

Segmento::Segmento() {}

Segmento::Segmento(PV2D inicio, PV2D vDesp){
	_puntoInicial = inicio;
	_vectorDesp = vDesp;
	_activo =false;
}

Segmento::~Segmento() {
}

PV2D Segmento::getPuntoInicial() {
	return _puntoInicial;
}

void Segmento::setPuntoInicial (PV2D punto) {
	_puntoInicial = punto;
}

PV2D Segmento::getVectorDesp() {
	return _vectorDesp;
}

void Segmento::setVectorDesp (PV2D desp) {
	_vectorDesp = desp;
}

void Segmento::draw(float r, float g, float b) {
	glBegin (GL_LINES);
		glColor3f(r, g, b);
		glVertex2d(_puntoInicial.getX(), _puntoInicial.getY() );
		glVertex2d(_puntoInicial.getX() + _vectorDesp.getX(), _puntoInicial.getY() + _vectorDesp.getY() );
	glEnd ();
}

void Segmento::activa() {
	_activo = true;
}

void Segmento::desactiva() {
	_activo = false;
}

bool Segmento::estaActivado() {
	return _activo;
}