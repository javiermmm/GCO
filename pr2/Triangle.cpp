//---------------------------------------------------------------------------
// Javier Martín Moreno-Manzanaro
//---------------------------------------------------------------------------

#include "Triangle.h"
#include "PV2D.h"

Triangle::Triangle(PV2D p1, PV2D p2, PV2D p3) {
	_vertices[0] = p1;
	_vertices[1] = p2;
	_vertices[2] = p3;
}

Triangle::~Triangle() {}

PV2D Triangle::getVertice(int i) {
	return _vertices[i];
}

void Triangle::setVertice(int i, PV2D p) {
	_vertices[i] = p;
}

void Triangle::draw(float r, float g, float b) {
	glBegin ( GL_TRIANGLES ) ;
		glColor3f(r, g, b);
		for (int i=0; i<3; i++)
			glVertex2d( _vertices[i].getX(), _vertices[i].getY());
	glEnd ();
}

//Los bordes del AVE ya no hacen falta como parametros, porque la transformación se hace fuera del metodo (en el fichero main)
//Este método ya no se usa, porque los triangulos de la escena se crean como poligonos convexo regulares de tres lados
bool Triangle::testPosicion (PV2D punto, GLdouble xLeft, GLdouble xRight, GLdouble yTop, GLdouble yBot, 
				   int HEIGHT, int WIDTH) {

	//Consigo los vertices del triangulo
	PV2D v0 = _vertices[0];//C
	PV2D v1 = _vertices[1];//A
	PV2D v2 = _vertices[2];//B

	//Calculo los vectores necesarios para calcular a y b: CP, CA y CB
	double CP_X = punto.getX() - v0.getX();
	double CP_Y = punto.getY() - v0.getY();
	double CA_X = v1.getX() - v0.getX();
	double CA_Y = v1.getY() - v0.getY();
	double CB_X = v2.getX() - v0.getX();
	double CB_Y = v2.getY() - v0.getY();

	//Calculamos a
	double numerador_a = (CP_X * (-CB_Y)) + (CP_Y * CB_X);   //Hacemos el producto escalar (x*x + y*y)
	double denominador_a = (CA_X * (-CB_Y)) + (CA_Y * CB_X); //teniendo en cuenta que debemos usar CB_izquierda (-CB_Y, CB_X)
	double a = numerador_a / denominador_a;

	//Calculamos b
	double numerador_b = (CP_X * (-CA_Y)) + (CP_Y * CA_X);   //Hacemos el producto escalar (x*x + y*y)
	double denominador_b = (CB_X * (-CA_Y)) + (CB_Y * CA_X); //teniendo en cuenta que debemos usar CA_izquierda (-CA_Y, CA_X)
	double b = numerador_b / denominador_b;

	//Comprobamos condiciones
	if  ((a >= 0) && (b >= 0) && ((a+b) <=1)) 
		return true;
	else 
		return false;
}