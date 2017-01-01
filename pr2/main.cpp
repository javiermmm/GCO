#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include "Triangle.h"
#include "PoligonoConvexo.h"
#include "Segmento.h"
#include "Escena.h"
#include "Constantes.h"

#include <iostream>
using namespace std;

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

// Viewport size
int WIDTH= 500, HEIGHT= 250;

// Scene visible area size
//GLdouble xLeft= 0.0, xRight= 500.0, yBot= 0.0, yTop= 250.0;

// Scene variables
//GLdouble xTriangle= 100.0, yTriangle= 100.0;
//GLdouble triangleWidth= 100.0, triangleHeight= 50.0;

//Triangle t0 = Triangle(PV2D (xTriangle, yTriangle), PV2D (xTriangle + triangleWidth, yTriangle), PV2D (xTriangle + triangleWidth, yTriangle + triangleHeight));
//Triangle t1 = Triangle(PV2D (300, 100), PV2D (400, 100), PV2D (300, 200));
//PoligonoConvexo p0 = PoligonoConvexo (PV2D (70, 180), 8, 50);
//PoligonoConvexo p1 = PoligonoConvexo (PV2D (400, 50), 6, 40);
//PoligonoConvexo p2 = PoligonoConvexo (PV2D (300, 150), 3, 70);
//PoligonoConvexo p3 = PoligonoConvexo (PV2D (140, 60), 3, 60);
//Segmento segmento = Segmento();

Estado estado = SELECCIONANDO;//Al iniciar, se pone por defecto el estado 'SELECCIONANDO'
Escena* escena;
bool animacion = false;
int pasosDados = 0;
bool inicioSegmentoFijado = false;

void intitGL(){

	glClearColor(1.0,1.0,1.0,1.0);
	glColor3f(1.0,0.0,0.0); 

	glPointSize(4.0);
	glLineWidth(2.0);

	// Viewport
    glViewport(0, 0, WIDTH, HEIGHT);
    
	// Model transformation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Scene Visible Area
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(escena->getXLeft(), escena->getXRight(), escena->getYBot(), escena->getYTop()); 
 }


void display(void){
  glClear( GL_COLOR_BUFFER_BIT );

  escena->dibujar(estado);

  glFlush();
  glutSwapBuffers();
}


void resize(int newWidth, int newHeight){
  //Resize Viewport
  WIDTH= newWidth;
  HEIGHT= newHeight;
  GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
  glViewport ( 0, 0, WIDTH, HEIGHT ) ;
  
  //Resize Scene Visible Area 
  //Se actualiza el área visible de la escena
  //para que su ratio coincida con ratioViewPort
  GLdouble SVAWidth= escena->getXRight()-escena->getXLeft();
  GLdouble SVAHeight= escena->getYTop()-escena->getYBot();
  GLdouble SVARatio= SVAWidth/SVAHeight;
  if (SVARatio >= RatioViewPort) {
	 // Increase SVAHeight
     GLdouble newHeight= SVAWidth/RatioViewPort;
	 GLdouble yMiddle= ( escena->getYBot()+escena->getYTop() )/2.0;
     escena->setYTop(yMiddle + newHeight/2.0);
     escena->setYBot(yMiddle - newHeight/2.0);
     }
  else {
     //Increase SVAWidth
     GLdouble newWidth= SVAHeight*RatioViewPort;
     GLdouble xMiddle= ( escena->getXLeft()+escena->getXRight() )/2.0;
	 escena->setXRight(xMiddle + newWidth/2.0);
     escena->setXLeft(xMiddle - newWidth/2.0);
  }

  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluOrtho2D(escena->getXLeft(), escena->getXRight(), escena->getYBot(), escena->getYTop());
}


void keySp (int key, int x, int y) {

	bool need_redisplay = true;

  switch (key) {
  case 27:  /* Escape key */
    //continue_in_main_loop = false; // (**)
	glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)
    break;

  case GLUT_KEY_LEFT:
  {
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();

	  //Calculamos el incremento como un porcentaje del ancho del area visible de la escena
	  double incremento = (escena->getXRight() -escena->getXLeft()) * 0.02;

	  //movemos las coordenadas XLeft y XRight hacia el mismo sentido en una cantidad de incremento
	  escena->setXLeft(escena->getXLeft() + incremento);
	  escena->setXRight(escena->getXRight() + incremento);
      gluOrtho2D(escena->getXLeft(), escena->getXRight(), escena->getYBot(), escena->getYTop());
	  break;
  }

  case GLUT_KEY_RIGHT:
  {
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();

	  //Calculamos el incremento como un porcentaje del ancho del area visible de la escena
	  double incremento = (escena->getXRight() -escena->getXLeft()) * 0.02;

	  //movemos las coordenadas XLeft y XRight hacia el mismo sentido en una cantidad de incremento
	  escena->setXLeft(escena->getXLeft() - incremento);
	  escena->setXRight(escena->getXRight() - incremento);
      gluOrtho2D(escena->getXLeft(), escena->getXRight(), escena->getYBot(), escena->getYTop());
	  break;
  }

  case GLUT_KEY_DOWN:
  {
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();

	  //Calculamos el incremento como un porcentaje del ancho del area visible de la escena
	  double incremento = (escena->getYTop() -escena->getYBot()) * 0.02;

	  //movemos las coordenadas YTop e YBot hacia el mismo sentido en una cantidad de incremento
	  escena->setYBot(escena->getYBot() + incremento);
	  escena->setYTop(escena->getYTop() + incremento);
      gluOrtho2D(escena->getXLeft(), escena->getXRight(), escena->getYBot(), escena->getYTop());
	  break;
  }

  case GLUT_KEY_UP:
  {
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();

	  //Calculamos el incremento como un porcentaje del ancho del area visible de la escena
	  double incremento = (escena->getYTop() -escena->getYBot()) * 0.02;

	  //movemos las coordenadas YTop e YBot hacia el mismo sentido en una cantidad de incremento
	  escena->setYBot(escena->getYBot() - incremento);
	  escena->setYTop(escena->getYTop() - incremento);
      gluOrtho2D(escena->getXLeft(), escena->getXRight(), escena->getYBot(), escena->getYTop());
	  break;
  }

  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}

void calculaCentroYBordesParaZoom (int nuevoAncho, int nuevoAlto) {
	
	double centroX = 0;
	double centroY = 0;

	//Extraemos las coordenadas del centro actual (porque no debe moverse)
	centroX = (escena->getXLeft() + escena->getXRight()) / 2.0;
	centroY = (escena->getYTop() + escena->getYBot()) / 2.0;
	
	//Calculamos los nuevos valores de los bordes del area visible en base al centro
	escena->setXRight(centroX + nuevoAncho/2.0);
	escena->setXLeft(centroX - nuevoAncho / 2.0);
	escena->setYTop(centroY + nuevoAlto / 2.0);
	escena->setYBot(centroY - nuevoAlto / 2.0);

	//Aplicamos los cambios
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(escena->getXLeft(), escena->getXRight(), escena->getYBot(), escena->getYTop());
}

void animate(int value) {
	animacion= escena->actualiza(pasosDados);
	if (estado == ANIMANDO && animacion)
		glutTimerFunc(intervalo, animate, 1);
	glutPostRedisplay();
}

void key(unsigned char key, int x, int y){
 
  bool need_redisplay = true;
  int nuevoAncho=0;
  int nuevoAlto=0;

  switch (key) {
  case 27:  /* Escape key */
    //continue_in_main_loop = false; // (**)
	glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop (*)
    break;

  case '+' :
  {
	//Calculamos los nuevos ancho y alto (incremento del 10%)
	nuevoAncho = (escena->getXRight() - escena->getXLeft()) / 1.1;
	nuevoAlto = (escena->getYTop() - escena->getYBot()) /1.1;

	calculaCentroYBordesParaZoom(nuevoAncho, nuevoAlto);

	break;
  }
  case '-' :
  {
	//Calculamos los nuevos ancho y alto (decremento del 10%)
	nuevoAncho = (escena->getXRight() - escena->getXLeft()) / 0.9;
	nuevoAlto = (escena->getYTop() - escena->getYBot()) / 0.9;

	calculaCentroYBordesParaZoom(nuevoAncho, nuevoAlto);

	break;
  }
   case '1' :
  {
	if (estado == ANIMANDO)
		pasosDados = 0;
	estado = SELECCIONANDO;
	break;
  }
  case '2' :
  {
	if (estado == ANIMANDO)
		pasosDados = 0;
	estado = SEGMENTO1;
	break;
  }
  case '3' :
  {
	if (estado == ANIMANDO)
		pasosDados = 0;
	estado = SEGMENTO2;
	break;
  }
  case '4' :
  {
	if (escena->segmentoActivado()) {//si segmento activo
		estado = ANIMANDO;
		animacion = true;
		escena->creaPelota();
		animate(1);
	}
	break;
  }
  case 'a' ://Prueba de animacion
  {
	estado = ANIMANDO;
	animacion = true;
	escena->creaPelota();
	animacion = escena->actualiza(pasosDados);
	break;
  }
  case 'c' :
  {
	  if (escena->segmentoActivado() && escena->getPoligonoSeleccionado() != NULL){
		  float tIn, tOut = 0;
		  if (escena->getPoligonoSeleccionado()->cyrusBeck(&escena->getInicioSegmento(), &escena->getVectorSegmento(), tIn, tOut)) {
			  cout << "El poligono seleccionado y el segmento se cortan en [" << tIn << ", " << tOut << "]" << endl;

			  //Calculamos el nuevo inicio (origen de la interseccion)
			  PV2D nuevoDespIni = escena->getVectorSegmento();
			  nuevoDespIni.multiplicaPorK(tIn);
			  PV2D nuevoIni = PV2D (escena->getInicioSegmento().getX() + nuevoDespIni.getX(), escena->getInicioSegmento().getY() + nuevoDespIni.getY());

			  //Calculamos el nuevo vector desplazamiento (desde el nuevo origen hasta fin de segmento o salida de la interseccion)
			  PV2D nuevoDespFin = escena->getVectorSegmento();
			  nuevoDespFin.multiplicaPorK(tOut - tIn);

			  //Establecemos el nuevo segmento activo en la escena
			  escena->setInicioSegmento(nuevoIni);
			  escena->setVectorSegmento(nuevoDespFin);

			  //Recolocamos la pelota al inicio del segmento. (si ya hay pelota la destruimos y si no la creamos al inicio del segmento) [Ver creaPelota]
			  //Esto tiene sentido porque seguimos teniendo segmento activo.
			  if (!animacion)
				escena->creaPelota();
		  }
		  else {
			  cout << "El poligono seleccionado y el segmento NO se cortan" << endl;
			  escena->desactivaSegmento();
		  }
	  }
	break;
  }
  default:
    need_redisplay = false;
    break;
  }//switch

  if (need_redisplay)
    glutPostRedisplay();
}

PV2D transformPV2AVE(int x, int y){
	//Convertimos las coordenadas. Para ello sacamos la proporcion entre pixel y coordenada abstracta (paréntesis de la derecha)
	//y lo multiplicamos por el numero de pixeles que recogemos del click para saber la cantidad de unidades abstractas.
	//Luego solo queda desplazar esa cantidad desde yTop o xLeft segun corresponda.
	int yNew = escena->getYTop() - y * ((escena->getYTop() - escena->getYBot())/ HEIGHT);
	int xNew = escena->getXLeft() + x * ((escena->getXRight() - escena->getXLeft())/ WIDTH);

	//corregimos las coordenadas con el grosor del marco. 2px para la x y 10 para la y
	yNew = yNew -10;
	xNew = xNew +2;

	//Lo metemos en un objeto de clase Punto
	return PV2D (xNew, yNew);
}

void mouseClick(int button, int state, int x, int y) {
	bool need_redisplay = true;

	switch (button) {
	case GLUT_LEFT_BUTTON:
	{
		if (state == GLUT_DOWN) {
			cout << "Pulsaste en la coordenada " << x << ", " << y << endl;
			PV2D p = transformPV2AVE(x, y);
			if (estado == SELECCIONANDO) {
				if (escena->getPoligono(0)->testPosicionInterior(p)){
					cout << "Esta coordenada esta dentro del poligono p0" << endl;
					escena->setPoligonoSeleccionado(escena->getPoligono(0));
				}
				else if (escena->getPoligono(1)->testPosicionInterior(p)){
					cout << "Esta coordenada esta dentro del poligono p1" << endl;
					escena->setPoligonoSeleccionado(escena->getPoligono(1));
				}
				else if (escena->getPoligono(2)->testPosicionInterior(p)){
					cout << "Esta coordenada esta dentro del poligono p2" << endl;
					escena->setPoligonoSeleccionado(escena->getPoligono(2));
				}
				else if (escena->getPoligono(3)->testPosicionInterior(p)){
					cout << "Esta coordenada esta dentro del poligono p3" << endl;
					escena->setPoligonoSeleccionado(escena->getPoligono(3));
				}
				/*
				else if (t0.testPosicion(p, escena->getXLeft(), escena->getXRight(), escena->getYTop(), escena->getYBot(), HEIGHT, WIDTH)) {
					cout << "Esta coordenada esta dentro del triangulo t0" << endl;
					t0.draw(0.5, 0.0, 0.0);
				}
				else if (t1.testPosicion(p, escena->getXLeft(), escena->getXRight(), escena->getYTop(), escena->getYBot(), HEIGHT, WIDTH)) {
					cout << "Esta coordenada esta dentro del triangulo t1" << endl;
					t1.draw(0.5, 0.0, 0.0);
				}*/
			}
			if (estado == SEGMENTO1){
				escena->setInicioSegmento(p);
				escena->desactivaSegmento();
				inicioSegmentoFijado = true;
			}
			if (estado == SEGMENTO2){
				if (inicioSegmentoFijado) { //Solo se permite fijar el fin del segmento si se ha fijado antes algun inicio
					PV2D vDesp = p.restaPuntos(escena->getInicioSegmento());
					escena->setVectorSegmento(vDesp);
					escena->activaSegmento();
				}
			}
		}	
	}
	default:
		need_redisplay = false;
		break;
	}//switch

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]){
  cout<< "Starting console..." << endl;

  escena = new Escena();

  int my_window; //my window's identifier

  //Initialization
  glutInitWindowSize(WIDTH, HEIGHT);
  glutInitWindowPosition (140, 140);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE );
  glutInit(&argc, argv);

  //Window construction
  my_window = glutCreateWindow( "Freeglut 2D-project" );
    
  //Callback registration
  glutReshapeFunc(resize);
  glutKeyboardFunc(key);
  glutDisplayFunc(display);
  glutSpecialFunc(keySp);
  glutMouseFunc(mouseClick);

  //OpenGL basic setting
  intitGL();


  // Freeglut's main loop can be stopped executing (**)
  //while ( continue_in_main_loop )
  //  glutMainLoopEvent();

  // Classic glut's main loop can be stopped after X-closing the window,
  // using the following freeglut's setting (*)
  glutSetOption ( GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION ) ;
    
  // Classic glut's main loop can be stopped in freeglut using (*)
  glutMainLoop(); 
  
  // We would never reach this point using classic glut
  system("PAUSE"); 
   
  delete escena;

  return 0;
}
