//---------------------------------------------------------------------------
// Javier Martín Moreno-Manzanaro
//---------------------------------------------------------------------------

#include "PoligonoConvexo.h"

PoligonoConvexo::PoligonoConvexo() {}

PoligonoConvexo::PoligonoConvexo(PV2D C, int N, int r) {

	//Nos guardamos los valores de los atributos
	_seleccionado = false;
	_centro = C;
	_numLados = N;
	_radio = r;
	_vertices = new PV2D [N];
	_normales = new PV2D [N];


	//Creamos los vertices
	double incrementoX = 0;
	double incrementoY= 0;
	float ang = (2 * 3.14159265) / N;
	double x = 0;
	double y = 0;

	for (int i= 0; i<N; i++){
		incrementoX= r*cos(i*ang);
		incrementoY= r*sin(i*ang);
		x= C.getX() + incrementoX;
		y= C.getY() + incrementoY;
		_vertices[i] = PV2D(x, y);
	}


	//Creamos las normales
	for (int i= 0; i<N; i++){
		PV2D vectorAux = _vertices[(i+1) % N].restaPuntos(_vertices[i]);
		vectorAux = vectorAux.vIzquierda(); //La normal de la arista P0P1, es el vector P1P0 por la izquierda
		vectorAux.multiplicaPorK(-1);
		vectorAux = vectorAux.normaliza();
		_normales[i] = vectorAux;
	}
}

PoligonoConvexo::~PoligonoConvexo() {
	delete [] _vertices;
	delete [] _normales;
}

PV2D PoligonoConvexo::getVertice(int i) {
	return _vertices[i];
}

PV2D PoligonoConvexo::getNormal(int i) {
	return _normales[i];
}

void PoligonoConvexo::setVertice(int i, PV2D p) {
	_vertices[i] = p;
}

void PoligonoConvexo::setNormal(int i, PV2D v) {
	_normales[i] = v;
}

void PoligonoConvexo::draw(float r, float g, float b) {
	glBegin (GL_POLYGON);
		glColor3f(r, g, b);
		for (int i=0; i<_numLados; i++){
			glVertex2d( _vertices[i].getX(), _vertices[i].getY());
		}
	glEnd ();
}

bool PoligonoConvexo::testPosicionInterior(PV2D punto) {

	//Un punto P está dentro de un poligono si para todos sus vertices Pi se cumple:
	//PiP · ni <= 0
	bool dentro = true;
	int i=0;
	while ((dentro) && (i>=0) && (i<_numLados)) {
		PV2D vector_Pi_P = punto.restaPuntos(_vertices[i]);
		double producto = vector_Pi_P.productoEscalar(_normales[i]);
		if (producto > 0)
			dentro = false;
		i++;
	}

	return dentro;
}

void PoligonoConvexo::selecciona(){
	_seleccionado = true;
}

void PoligonoConvexo::deselecciona(){
	_seleccionado = false;
}

bool PoligonoConvexo::estaSeleccionado(){
	return _seleccionado;
}

PV2D PoligonoConvexo::getCentro() {
	return _centro;
}

void PoligonoConvexo::setCentro(PV2D c) {
	_centro = c;
}

int PoligonoConvexo::getNumLados() {
	return _numLados;
}

void PoligonoConvexo::setNumLados(int n) {
	_numLados = n;
}

int PoligonoConvexo::getRadio() {
	return _radio;
}

void PoligonoConvexo::setRadio (int r) {
	_radio = r;
}

bool PoligonoConvexo::cyrusBeck (PV2D* P, PV2D* v, //R = P + tv
								 float& tIn, float& tOut){ //Salida del algoritmo

	tIn= 0; 
	tOut= 1; //R es un segmento
	int i= 0; 
	bool encontrado= false;
	while(!encontrado && i<_numLados){
		//Calcular el corte de R contra la arista extendida <Pi, ni>
		PV2D vector_Pi_P = P->restaPuntos(_vertices[i]);
		double numerador= (-1) * vector_Pi_P.productoEscalar(_normales[i]);
		double denominador= v->productoEscalar(_normales[i]);
		if( (-numerador >= 0) && (denominador == 0) ) //paralelismo por fuera o coincidencia
			encontrado= true;
		else if( ! (((-numerador) < 0) && (denominador == 0)) ){ //No paralelismo por dentro. Intersección usual
			float tHit= numerador/denominador;
			if( denominador < 0) //tHit es de entrada
				tIn= max(tIn, tHit);
			else if( denominador > 0 ) //tHit es de salida
				tOut= min(tOut, tHit);
			encontrado= tIn>tOut;
		}//else if //Intersección usual
		i++;
	}//while
	return !encontrado;
}