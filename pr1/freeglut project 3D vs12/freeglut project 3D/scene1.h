//---------------------------------------------------------------------------
// Ana Gil Luezas
//---------------------------------------------------------------------------
#ifndef Scene1H
#define Scene1H

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
//#include <GL/freeglut.h>  // teapot de glut
//#include <GL/glut.h>
//---------------------------------------------------------------------------
class scene{
protected:
  struct sphere{
	GLUquadricObj *pEsf;
    GLint ang;
    GLdouble dis;
  } estrella, planeta, satelite;
  
  GLUquadricObj *orbitaP, *orbitaS, *orbitaSputnik; 

  struct SatArti {
	  GLint ang;
	  GLdouble dis;
  } sputnik;
  
  struct Color {
	  GLfloat R;
	  GLfloat G;
	  GLfloat B;
  };

  struct Vertice{
	  GLfloat x;
	  GLfloat y;
	  GLfloat z;
	  Color color;
  };

  struct Normal{
	  GLfloat x;
	  GLfloat y;
	  GLfloat z;
  };

  struct Cara {
	  GLint numVertices;
	  GLint indVertices[3];
	  GLint indNormales[3];
  };

  struct sateliteMalla {
	  Vertice tablaVertices[9];
	  Normal tablaNormales[8];
	  Cara tablaCaras[8];
  } sateliteArtificial;
  
  void drawEstrella();
  void drawPlaneta();
  void drawSatelite();
  void drawOrbitaP();
  void drawOrbitaS();
  void drawOrbitaSputnik();
  void dibujaEjes();
  void triangulo();
  void piramide();
  void drawSputnik();
  void drawSateliteArtificial();
public:
  scene();
  ~scene();
  void iniciar();
  void dibujar();
  void incAngEstrella(GLint a);    // incrementa el ángulo de la Estrella
  void incAngPlaneta(GLint a);    // incrementa el ángulo del Planeta
  void incAngSatelite(GLint a);    // incrementa el ángulo del Satelite
  void incAngSputnik(GLint a);    // incrementa el ángulo del Satelite Artificial
  void setDisEstrella(GLdouble d); // establece la distancia
  GLdouble getDisEstrella(){ return estrella.dis; }
  GLint getAngEstrella(){ return estrella.ang; }
};

#endif

