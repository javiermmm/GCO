//---------------------------------------------------------------------------
// Ana Gil Luezas
//---------------------------------------------------------------------------
#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <Math.h>

#include <GL/freeglut.h>
//#include <GL/glut.h>

//#include <iostream>  // para usar la consola
//using namespace std;
#include "scene1.h"  // la escena que se quiere visualizar
//---------------------------------------------------------------------------
bool luzSol = true;
bool ortho = true;
float ang = 45;
// Viewport size  (left=right=0)
struct viewPort{GLsizei w; GLsizei h;} Vp = {400, 400};
// Camera parameters
struct viewCamera{GLdouble eyeX, eyeY, eyeZ;
        GLdouble lookX, lookY, lookZ;
        GLdouble upX, upY, upZ;} V = {100,100,100, 0,0,0, 0,1,0};
// Viewing frustum parameters
struct viewVolume{GLdouble xRight, xLeft;
        GLdouble yTop, yBot;
        GLdouble zNear, zFar;} Pj = {200,-200, 200,-200, 1,1000};
GLdouble scale = 1;
// Scene
scene escena;
// prototipos
void initGL();
void resize(int wW, int wH);
void display();
void keyPres(unsigned char key, int mX, int mY);
void keySp(int key, int mX, int mY);
//---------------------------------------------------------------------------

// programa principal
int main(int argc, char* argv[]){ 
  // Initialization 
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
  glutInitWindowSize(Vp.w, Vp.h); 
  glutInitWindowPosition(100,100);
  glutInit(&argc,argv);
  // Window construction
  int win=glutCreateWindow("Ventana FreeGLUT - Escena 3D");
  // Callback registration
  glutDisplayFunc(display);
  glutReshapeFunc(resize);
  glutKeyboardFunc(keyPres);
  glutSpecialFunc(keySp);
  // OpenGL basic setting
  initGL();
  // iniciar la escena
  escena.iniciar();
  // Classic glut's main loop can be stopped after X-closing the window, using freeglut's setting
  glutSetOption(GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
  glutMainLoop();  //while (continue_in_main_loop) glutMainLoopEvent();
  // Window destruction (never reach this point using classic glut)
  glutDestroyWindow(win);
  // liberar la escena
  return 0;
}
//---------------------------------------------------------------------------

void initGL(){
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);
  glEnable(GL_COLOR_MATERIAL);   

   // Light0  set up
  glEnable(GL_LIGHT0);
  GLfloat LuzDifusa[4]={0.4, 0.4, 0.4, 1.0};
  glLightfv(GL_LIGHT0, GL_DIFFUSE, LuzDifusa);
  /*GLfloat LuzAmbiente[4]={0.3f, 0.3f, 0.3f, 1.0f};
  glLightfv(GL_LIGHT0, GL_AMBIENT, LuzAmbiente);
  */

  glClearColor(0.6f, 0.7f, 0.8f, 1.0f);   // color de fondo (alpha=1 -> opaco)

  // Viewport set up
  glViewport(0,0, Vp.w, Vp.h);  // Vp
  // Camera set up
  glMatrixMode(GL_MODELVIEW);   // VIEW
  glLoadIdentity();
  gluLookAt(V.eyeX,V.eyeY,V.eyeZ, V.lookX,V.lookY,V.lookZ, V.upX,V.upY,V.upZ);
   // Frustum set up
  glMatrixMode(GL_PROJECTION);  // Pr
  glLoadIdentity();
  glOrtho(Pj.xLeft,Pj.xRight, Pj.yBot,Pj.yTop, Pj.zNear,Pj.zFar);
}
//---------------------------------------------------------------------------

void resize(int wW, int wH){
  // Viewport set up     
  Vp.w = wW; Vp.h = wH; 
  glViewport(0,0, Vp.w, Vp.h); 
  // Frustum set up
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  Pj.xRight = Vp.w/ 2.0 / scale; Pj.xLeft = -Pj.xRight; 
  Pj.yTop = Vp.h/2.0 / scale;  Pj.yBot = -Pj.yTop; 
  glOrtho(Pj.xLeft,Pj.xRight, Pj.yBot,Pj.yTop, Pj.zNear,Pj.zFar);
  //display();
  glutPostRedisplay();
}
//---------------------------------------------------------------------------

void display(void) {

  glMatrixMode(GL_MODELVIEW);  // MODEL
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  
  //scene
  //glPushMatrix();
  glPolygonMode(GL_FRONT, GL_LINE);  
  //glShadeModel(GL_FLAT); 
  glScaled(100, 100, 100);
  
  glScaled(1.0/100, 1.0/100, 1.0/100);
  glPolygonMode(GL_FRONT, GL_FILL);
  //glShadeModel(GL_SMOOTH);
  //glPopMatrix();

  //Ponemos la posicion de la luz de la camara justo antes de dibujar la escena para que se actualice
  //con la posicion de la propia camara
  GLfloat posLuz0[4] = { V.eyeX, V.eyeY, V.eyeZ, 0.0 };
  glLightfv(GL_LIGHT0, GL_POSITION, posLuz0);

  escena.dibujar();

  //glFlush();
  glutSwapBuffers();
}
//---------------------------------------------------------------------------

void keyPres(unsigned char key, int mX, int mY){
  bool need_redisplay = true;
  if(key == 27)  /* Escape key */  //continue_in_main_loop = false; (**)
	   glutLeaveMainLoop (); //Freeglut's sentence for stopping glut's main loop 
  else if(key == '+') { 
	  if(scale < 10.) {
		  scale +=0.25; 
		  resize(Vp.w, Vp.h);
	  } 
  }
  else if(key == '-') { 
	  if(scale > 0.3) {
		  scale -=0.25; 
		  resize(Vp.w, Vp.h);
	  } 
  }
  else if (key == 'd') 
	  escena.setDisEstrella(escena.getDisEstrella() + 5);
  else if (key == 't') { //tilling
	  int left = 0;
	  int bottom = 0;
	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  //Limpiamos el buffer
	  for (int i=0; i<4; i++) {
		  left = 0;
		  for (int j=0; j<4; j++) {
			glViewport(left, bottom, Vp.w/4, Vp.h/4); //dividimos entre 4 por la proporcion del viewport que esta a 400x400
			escena.dibujar();
			left = left + Vp.w/4;
		  }
		  bottom = bottom + Vp.h/4;
	  }
	  glViewport(0, 0, Vp.w, Vp.h); //dejamos el viewport como estaba
	  glutSwapBuffers(); //volcamos los buffers
	  need_redisplay = false; //indicamos que no se repinte
  }

  else if(key == 'x') { //perfil
	  //ponemos la proyeccion ortogonal
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  Pj = { 200, -200, 200, -200, 1, 1000 };
	  glOrtho(Pj.xLeft, Pj.xRight, Pj.yBot, Pj.yTop, Pj.zNear, Pj.zFar); // Pr=?
	  ortho = true;

	  //cambiamos la posicion de la camara
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  V = { 200, 0, 0, 0, 0, 0, 0, 1, 0 };
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);
  }
  else if (key == 'y')  {//planta
	  //ponemos la proyeccion ortogonal
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  Pj = { 200, -200, 200, -200, 1, 1000 };
	  glOrtho(Pj.xLeft, Pj.xRight, Pj.yBot, Pj.yTop, Pj.zNear, Pj.zFar); // Pr=?
	  ortho = true;

	  //cambiamos la posicion de la camara
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  V = { 0, 200, 0, 0, 0, 0, 0, 0, 1 };
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);
  }
	  
  else if (key == 'z')  {//alzado
	  //ponemos la proyeccion ortogonal
	  glMatrixMode(GL_PROJECTION);
	  glLoadIdentity();
	  Pj = { 200, -200, 200, -200, 1, 1000 };
	  glOrtho(Pj.xLeft, Pj.xRight, Pj.yBot, Pj.yTop, Pj.zNear, Pj.zFar); // Pr=?
	  ortho = true;

	  //cambiamos la posicion de la camara
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  V = { 0, 0, 200, 0, 0, 0, 0, 1, 0};
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);
  }
  
  else if (key == 'p'){//Cambio de perspectiva
	  //posicionamos la camara
	  V = { 500, 500, 500, 0, 0, 0, 0, 1, 0};
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);

	  if (ortho) { //ponemos proyeccion
		  glMatrixMode(GL_PROJECTION);
		  glLoadIdentity();
		  Pj.zNear = 300;
		  glFrustum(Pj.xLeft, Pj.xRight, Pj.yBot, Pj.yTop, Pj.zNear, Pj.zFar); // Pr=?
		  ortho = false;
	  }
	  else { //ponemos ortho
		  glMatrixMode(GL_PROJECTION);
		  glLoadIdentity();
		  glOrtho(Pj.xLeft, Pj.xRight, Pj.yBot, Pj.yTop, Pj.zNear, Pj.zFar); // Pr=?
		  ortho = true;
	  }
  }
  else if (key == 'n'){ //Alejar camara
	  //calculamos el vector
	  float vectorX = V.eyeX - V.lookX;
	  float vectorY = V.eyeY - V.lookY;
	  float vectorZ = V.eyeZ - V.lookZ;

	  //calculamos magnitud
	  float magnitud = sqrt(pow(vectorX, 2) + pow(vectorY, 2) + pow(vectorZ, 2));

	  //calculamos direccion
	  float dirX = vectorX / magnitud;
	  float dirY = vectorY / magnitud;
	  float dirZ = vectorZ / magnitud;

	  //actualizamos posicion de la camara (ex = ex + t*dx)
	  V = { V.eyeX + 10 * (dirX), V.eyeY + 10 * (dirY), V.eyeZ + 10 * (dirZ), V.lookX + 10 * (dirX), V.lookY + 10 * (dirY), V.lookZ + 10 * (dirZ), V.upX, V.upY, V.upZ };
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);
  }
  else if (key == 'N'){//acercar cámara
	  //calculamos el vector
	  float vectorX = V.eyeX - V.lookX;
	  float vectorY = V.eyeY - V.lookY;
	  float vectorZ = V.eyeZ - V.lookZ;

	  //calculamos magnitud
	  float magnitud = sqrt(pow(vectorX, 2) + pow(vectorY, 2) + pow(vectorZ, 2));

	  //calculamos direccion
	  float dirX = vectorX / magnitud;
	  float dirY = vectorY / magnitud;
	  float dirZ = vectorZ / magnitud;

	  //actualizamos posicion de la camara (ex = ex - t*dx)
	  V = { V.eyeX - 10 * (dirX), V.eyeY - 10 * (dirY), V.eyeZ - 10 * (dirZ), V.lookX - 10 * (dirX), V.lookY - 10 * (dirY), V.lookZ - 10 * (dirZ), V.upX, V.upY, V.upZ };
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);
  }
  else if (key == 'u'){// mover cámara a la derecha
	  //calculamoscalculamos los vectores
	  float vectorNX = V.eyeX - V.lookX;
	  float vectorNY = V.eyeY - V.lookY;
	  float vectorNZ = V.eyeZ - V.lookZ;
	  float vectorUX = V.upY * vectorNZ - V.upZ * vectorNY; //(producto vectorial)
	  float vectorUY = V.upZ * vectorNX - V.upX * vectorNZ;
	  float vectorUZ = V.upX * vectorNY - V.upY * vectorNX;

	  //calculamos magnitud
	  float magnitud = sqrt(pow(vectorUX, 2) + pow(vectorUY, 2) + pow(vectorUZ, 2));

	  //calculamos la direccion
	  float dirX = vectorUX / magnitud;
	  float dirY = vectorUY / magnitud;
	  float dirZ = vectorUZ / magnitud;

	  //actualizamos posicion de la camara (ex = ex + t*dx)
	  V = { V.eyeX + 10 * (dirX), V.eyeY + 10 * (dirY), V.eyeZ + 10 * (dirZ), V.lookX + 10 * (dirX), V.lookY + 10 * (dirY), V.lookZ + 10 * (dirZ), V.upX, V.upY, V.upZ };
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);
  }
  else if (key == 'U'){//mover cámara a la izquierda
	  //calculamos los vectores
	  float vectorNX = V.eyeX - V.lookX;
	  float vectorNY = V.eyeY - V.lookY;
	  float vectorNZ = V.eyeZ - V.lookZ;
	  float vectorUX = V.upY * vectorNZ - V.upZ * vectorNY; //(producto vectorial)
	  float vectorUY = V.upZ * vectorNX - V.upX * vectorNZ;
	  float vectorUZ = V.upX * vectorNY - V.upY * vectorNX;

	  //calculamos magnitud
	  float magnitud = sqrt(pow(vectorUX, 2) + pow(vectorUY, 2) + pow(vectorUZ, 2));

	  //calculamos direccion
	  float dirX = vectorUX / magnitud;
	  float dirY = vectorUY / magnitud;
	  float dirZ = vectorUZ / magnitud;

	  //Cambiamos posicion de la camara
	  V = { V.eyeX - 10 * (dirX), V.eyeY - 10 * (dirY), V.eyeZ - 10 * (dirZ), V.lookX - 10 * (dirX), V.lookY - 10 * (dirY), V.lookZ - 10 * (dirZ), V.upX, V.upY, V.upZ };
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);
  }
  else if (key == 'v'){//mover cámara arriba
	  //calculamos los vectores
	  float vectorNX = V.eyeX - V.lookX;
	  float vectorNY = V.eyeY - V.lookY;
	  float vectorNZ = V.eyeZ - V.lookZ;
	  float vectorUX = V.upY * vectorNZ - V.upZ * vectorNY; //(productos vectoriales)
	  float vectorUY = V.upZ * vectorNX - V.upX * vectorNZ;
	  float vectorUZ = V.upX * vectorNY - V.upY * vectorNX;
	  float vectorVX = vectorNY * vectorUZ - vectorNZ * vectorUY;
	  float vectorVY = vectorNZ * vectorUX - vectorNX * vectorUZ;
	  float vectorVZ = vectorNX * vectorUY - vectorNY * vectorUX;

	  //calculamos la magnitud
	  float magnitud = sqrt(pow(vectorVX, 2) + pow(vectorVY, 2) + pow(vectorVZ, 2));

	  //calculamos direccion
	  float dirX = vectorVX / magnitud;
	  float dirY = vectorVY / magnitud;
	  float dirZ = vectorVZ / magnitud;

	  //cambiamos posicion de la camara
	  V = { V.eyeX + 10 * (dirX), V.eyeY + 10 * (dirY), V.eyeZ + 10 * (dirZ), V.lookX + 10 * (dirX), V.lookY + 10 * (dirY), V.lookZ + 10 * (dirZ), V.upX, V.upY, V.upZ };
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);
  }
  else if (key == 'V'){//mover cámara abajo
	  //calculamos vectores
	  float vectorNX = V.eyeX - V.lookX;
	  float vectorNY = V.eyeY - V.lookY;
	  float vectorNZ = V.eyeZ - V.lookZ;
	  float vectorUX = V.upY * vectorNZ - V.upZ * vectorNY; //(productos vectoriales)
	  float vectorUY = V.upZ * vectorNX - V.upX * vectorNZ;
	  float vectorUZ = V.upX * vectorNY - V.upY * vectorNX;
	  float vectorVX = vectorNY * vectorUZ - vectorNZ * vectorUY;
	  float vectorVY = vectorNZ * vectorUX - vectorNX * vectorUZ;
	  float vectorVZ = vectorNX * vectorUY - vectorNY * vectorUX;

	  //calculamos magnitud
	  float magnitud = sqrt(pow(vectorVX, 2) + pow(vectorVY, 2) + pow(vectorVZ, 2));

	  //calculamos direccion
	  float dirX = vectorVX / magnitud;
	  float dirY = vectorVY / magnitud;
	  float dirZ = vectorVZ / magnitud;

	  //cambiamos posicion de la camara
	  V = { V.eyeX - 10 * (dirX), V.eyeY - 10 * (dirY), V.eyeZ - 10 * (dirZ), V.lookX - 10 * (dirX), V.lookY - 10 * (dirY), V.lookZ - 10 * (dirZ), V.upX, V.upY, V.upZ };
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);
  }
  else if (key == 'g'){//rotar cámara
	  ang = (int) (ang + 5.0) % 360;
	  //obviamos la Y porque calculamos la circuferencia en 2D
	  float vectorNX = V.eyeX - V.lookX;
	  float vectorNZ = V.eyeZ - V.lookZ;
	  float radio = sqrt(pow(vectorNX, 2) + pow(vectorNZ, 2));
	  //0.01745 es el resultado de dividir PI /180, lo cuál es necesario porque las funciones trigonómetricas
	  //sin y cos reciben como argumento el águlo en radianes, y es necesario hacer la conversión
	  V = { radio * cos(ang * 0.01745), V.eyeY, radio * sin(ang * 0.01745), V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ };
	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);
  }
  else if (key == 's') { //Rotaciones del sistema solar
	  escena.incAngEstrella(5); 
	  escena.incAngPlaneta(5);
	  escena.incAngSatelite(12);
	  escena.incAngSputnik(20);
  }
  else if(key == 'i') { //iniciar la escena
	  escena.iniciar();

	  glMatrixMode(GL_MODELVIEW);
	  glLoadIdentity();
	  V = { 100, 100, 100, 0, 0, 0, 0, 1, 0 };
	  gluLookAt(V.eyeX, V.eyeY, V.eyeZ, V.lookX, V.lookY, V.lookZ, V.upX, V.upY, V.upZ);

	  glMatrixMode(GL_PROJECTION);  // Pr
	  glLoadIdentity();
	  Pj = { 200, -200, 200, -200, 1, 1000 };
	  glOrtho(Pj.xLeft, Pj.xRight, Pj.yBot, Pj.yTop, Pj.zNear, Pj.zFar);
  }
  else if (key == '1'){//encender/apagar la luz del sol
	  if (luzSol) {
		  glDisable(GL_LIGHT1);
		  luzSol = false;
	  }
	  else {
		  glEnable(GL_LIGHT1);
		  luzSol = true;
	  }
  }
  else 
	  need_redisplay = false;

  if (need_redisplay) 
	  glutPostRedisplay();
}
//---------------------------------------------------------------------------

void keySp(int key, int mX, int mY){
  bool need_redisplay = true;
  if(key == GLUT_KEY_UP) glRotatef(5.0, 1.0,0.0,0.0);   
  else if (key == GLUT_KEY_DOWN) glRotatef(-5.0, 1.0,0.0,0.0);  
  else if (key == GLUT_KEY_RIGHT) glTranslatef(5.0, 0.0,0.0); 
  else if(key == GLUT_KEY_LEFT) glTranslatef(-5.0, 0.0,0.0); 
  else need_redisplay = false;

  if (need_redisplay) glutPostRedisplay();
}
//---------------------------------------------------------------------------
