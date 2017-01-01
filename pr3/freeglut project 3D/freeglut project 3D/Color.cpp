//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "Color.h"

Color::Color() {}

Color::Color(GLfloat rojo, GLfloat verde, GLfloat azul) {
	red = rojo;
	green = verde;
	blue = azul;
}

Color::~Color() {}

GLfloat Color::getR() {
	return red;
}

GLfloat Color::getG() {
	return green;
}

GLfloat Color::getB() {
	return blue;
}

void Color::setR(GLfloat r) {
	red = r;
}

void Color::setG(GLfloat g) {
	green = g;
}

void Color::setB(GLfloat b) {
	blue = b;
}