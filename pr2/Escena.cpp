//---------------------------------------------------------------------------
// Javier Martín Moreno-Manzanaro
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#include "Escena.h"
//---------------------------------------------------------------------------

Escena::Escena(){
  _numPoligonos = 4;
  _poligonoSeleccionado = NULL;
  _pelota = NULL;
  _segmento = new Segmento();
  iniciar();
}

Escena::~Escena(){

  //Primero destruimos los poligonos de la escena
  for (int i=0; i<4; i++) {
	  delete _poligonos[i];
  }

  //luego destruimos la pelota que animamos (si hay)
  if (_pelota != NULL) {
	  delete _pelota;
  }

  //Por último borramos el segmento (este activo o no)
  delete _segmento;
}

void Escena::iniciar(){

	//Establecemos las medidas del Area Visible de la Escena
	_xLeft = 0.0; 
	_xRight = 500.0; 
	_yBot = 0.0; 
	_yTop = 250.0;

	//Creamos los poligonos de la escena
	_poligonos[0] = new PoligonoConvexo (PV2D (70, 180), 8, 50);
	_poligonos[1] = new PoligonoConvexo (PV2D (400, 50), 6, 40);
	_poligonos[2] = new PoligonoConvexo (PV2D (300, 150), 3, 70);
	_poligonos[3] = new PoligonoConvexo (PV2D (140, 60), 3, 60);
}

void Escena::dibujar(Estado estado){

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Dibujamos los poligonos
	for (int i=0; i<_numPoligonos; i++) {
		_poligonos[i]->draw(1.0, 0.0, 0.0);
	}

	//Si hay un poligono seleccionado, lo redibujamos para cambiarle el color
	if (_poligonoSeleccionado != NULL)
		_poligonoSeleccionado->draw(0.7, 0.0, 0.0);

	//Si hay un segmento activo, lo pintamos
	if (_segmento->estaActivado())
		_segmento->draw(0.0, 0.0, 0.0);

	//Si estamos en "Modo animacion", y hay un segmento activo, pintamos la pelota.
	if (estado == ANIMANDO && _segmento->estaActivado())
		_pelota->draw(0.0, 1.0, 0.0);
}

GLdouble Escena::getXLeft() {
	return _xLeft;
}

GLdouble Escena::getXRight() {
	return _xRight;
}

GLdouble Escena::getYTop() {
	return _yTop;
}

GLdouble Escena::getYBot() {
	return _yBot;
}

void Escena::setXLeft(GLdouble xLeft) {
	_xLeft = xLeft;
}

void Escena::setXRight(GLdouble xRight) {
	_xRight = xRight;
}

void Escena::setYTop(GLdouble yTop) {
	_yTop = yTop;
}

void Escena::setYBot(GLdouble yBot) {
	_yBot = yBot;
}

PoligonoConvexo* Escena::getPoligono(int i) {
	return _poligonos[i];
}

PV2D Escena::getInicioSegmento() {
	return _segmento->getPuntoInicial();
}

void Escena::setInicioSegmento(PV2D ini) {
	_segmento->setPuntoInicial(ini);
}

PV2D Escena::getVectorSegmento() {
	return _segmento->getVectorDesp();
}

void Escena::setVectorSegmento(PV2D vDesp) {
	_segmento->setVectorDesp(vDesp);
}

void Escena::activaSegmento() {
	_segmento->activa();
}

void Escena::desactivaSegmento() {
	_segmento->desactiva();
}

bool Escena::segmentoActivado() {
	return _segmento->estaActivado();
}

PoligonoConvexo* Escena::getPoligonoSeleccionado() {
	return _poligonoSeleccionado;
}

void Escena::setPoligonoSeleccionado(PoligonoConvexo* poligono) {
	_poligonoSeleccionado = poligono;
}

void Escena::creaPelota() {
	//si trato de crear otra pelota, cuando ya existe una, la borro antes...
	if (_pelota != NULL)
		delete _pelota;
	if (_segmento->estaActivado()){//... y solo tiene sentido crearla si hay un segmento activo
		_pelota = new PoligonoConvexo(_segmento->getPuntoInicial(), 25, 6);
	}
}

bool Escena::actualiza(int& pasosDados) {

	PV2D centroActual = _pelota->getCentro();
	PV2D finSegmento = PV2D (_segmento->getPuntoInicial().getX() + _segmento->getVectorDesp().getX(),  _segmento->getPuntoInicial().getY() + _segmento->getVectorDesp().getY());
	bool animando = true;

	if (animando) {
		//si el centro de la pelota no está al final del segmento...
		if (!((int) centroActual.getX() == (int)finSegmento.getX()  &&  (int)centroActual.getY() == (int)finSegmento.getY())) {
			//hacemos la interpolación
			float Ti = (float) pasosDados / numPuntosIntermedios;
			float x = (_segmento->getPuntoInicial().getX() * (1 -Ti)) + ((_segmento->getPuntoInicial().getX() + _segmento->getVectorDesp().getX()) * Ti);
			float y = (_segmento->getPuntoInicial().getY() * (1 -Ti)) + ((_segmento->getPuntoInicial().getY() + _segmento->getVectorDesp().getY()) * Ti);
			PV2D nuevoCentro = PV2D (x, y);

			//reconstruimos la pelota
			if (_pelota != NULL) {
				delete _pelota;
				_pelota = new PoligonoConvexo(nuevoCentro, 25, 6);
			}

			//aumentamos en uno el numero de pasos que hemos dado para llegar al final
			pasosDados++;
			bool animando = true;
		}
		else { //si la pelota ha llegado al final
			//se acaba la animacion y ponemos a cero el contador de pasos dados
			pasosDados = 0;
			animando = false;
		}
	}
	return animando;
}