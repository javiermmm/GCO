//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "TAfin.h"
#include <math.h>

TAfin:: TAfin() {
	m = new GLfloat[16];
    //To do: hacer que m sea la identidad [hecho]
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glGetFloatv(GL_MODELVIEW_MATRIX,m);
	glPopMatrix();
}

TAfin:: ~TAfin() {
	delete[] m;
}

GLfloat* TAfin::dameMatrizModelado() {
	//To do [hecho]
	return m;
}

void TAfin:: traslada(GLfloat X, GLfloat Y, GLfloat Z) {   
	//To do [hecho]
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glTranslatef(X,Y,Z);
		GLfloat* mm = new GLfloat[16];
		glGetFloatv(GL_MODELVIEW_MATRIX,mm);
	glPopMatrix();
	postMultiplica(mm);
}

void TAfin:: escala(GLfloat fX, GLfloat fY, GLfloat fZ) {
	//To do  [hecho]
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glScalef(fX,fY,fZ);
		GLfloat* mm = new GLfloat[16];
		glGetFloatv(GL_MODELVIEW_MATRIX,mm);
	glPopMatrix();
	postMultiplica(mm);
}

void TAfin:: rota(GLfloat alfa, GLfloat fX, GLfloat fY, GLfloat fZ) {
	 //To do [hecho]
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadIdentity();
		glRotatef(alfa,fX,fY,fZ);
		GLfloat* mm = new GLfloat[16];
		glGetFloatv(GL_MODELVIEW_MATRIX,mm);
	glPopMatrix();
	postMultiplica(mm);
}

void TAfin:: postMultiplica(GLfloat* mm) {
	 //To do [hecho]
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
		glLoadMatrixf(m);
		glMultMatrixf(mm);
		glGetFloatv(GL_MODELVIEW_MATRIX,m);
	glPopMatrix();
}


