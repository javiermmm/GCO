//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#ifndef Color_H_
#define Color_H_

#include <GL/freeglut.h>

class Color{
	private:
		GLfloat red;
		GLfloat green;
		GLfloat blue;
	public:
		Color();
		Color(GLfloat rojo, GLfloat verde, GLfloat azul);
		~Color();
		GLfloat getR();
		GLfloat getG();
		GLfloat getB();
		void setR(GLfloat r);
		void setG(GLfloat g);
		void setB(GLfloat b);
};
#endif