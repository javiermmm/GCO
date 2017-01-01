//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include <Windows.h>
#include <gl/GL.h>
#include <gl/GLU.h> 

#include <GL/freeglut.h>
//#include <GL/glut.h>

#include <iostream>
using namespace std;

#include "Escena.h"
#include "Coche.h"
#include "Toro.h"
#include "Prisma.h"
#include "MallaRevolucion.h"
#include "Copa.h"

// Freeglut parameters
// Flag telling us to keep processing events
// bool continue_in_main_loop= true; //(**)

Escena* escena;
Coche* coche;
Toro* toro;
Prisma* prisma;
MallaRevolucion* mallaRevolucion;
Copa* copa;

bool e, c, t, p, r, X;

//Scene variables
GLint angX, angY, angZ; 

// Viewport size
int WIDTH= 500, HEIGHT= 500;

// Viewing frustum parameters
GLdouble xRight=10, xLeft=-xRight, yTop=10, yBot=-yTop, N=1, F=1000;

// Camera parameters
GLdouble eyeX=10.0, eyeY=10.0, eyeZ=10.0;
GLdouble lookX=0.0, lookY=0.0, lookZ=0.0;
GLdouble upX=0, upY=1, upZ=0;

void buildSceneObjects() {  	 	 
    angX=0;
    angY=0;
    angZ=0;
	escena = new Escena();
	coche = new Coche();
	toro = new Toro();
	prisma = new Prisma();
	mallaRevolucion = new MallaRevolucion();
	copa = new Copa();
	e=true;
	c=false;
	t=false;
	p=false;
	r=false;
	X=false;
}

void initGL() {	 		 
	glClearColor(0.6f,0.7f,0.8f,1.0);

	buildSceneObjects();
	glEnable(GL_LIGHTING); 	 
	glEnable(GL_LIGHT2);
    GLfloat d[]={0.6f, 0.7f, 0.8f, 1.0f};
    glLightfv(GL_LIGHT2, GL_DIFFUSE, d);
    GLfloat a[]={0.5, 0.5, 0.5, 1.0};
    glLightfv(GL_LIGHT2, GL_AMBIENT, a);
	GLfloat p[]={10.0, 10.0, 10.0, 1.0};	 
	glLightfv(GL_LIGHT2, GL_POSITION, p);
	  
	glEnable(GL_COLOR_MATERIAL);	 
	glEnable(GL_DEPTH_TEST);	 
	glEnable(GL_NORMALIZE);
	glShadeModel(GL_SMOOTH); 

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(eyeX, eyeY, eyeZ, lookX, lookY, lookZ, upX, upY, upZ);

	// Viewport set up
    glViewport(0, 0, WIDTH, HEIGHT);       
 }

void display(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

	// Drawing axes
	glBegin( GL_LINES );
		glColor3f(1.0,0.0,0.0);   
		glVertex3f(0, 0, 0);
		glVertex3f(20, 0, 0);	     
	 
		glColor3f(0.0,1.0,0.0); 
		glVertex3f(0, 0, 0);
		glVertex3f(0, 20, 0);	 
	 
		glColor3f(0.0,0.0,1.0); 
		glVertex3f(0, 0, 0);
		glVertex3f(0, 0, 20);			
	glEnd();
	
	// Drawing the scene
	glMatrixMode(GL_MODELVIEW);	 
	glPushMatrix();				 
		glRotated(angX, 1, 0, 0);
        glRotated(angY, 0, 1, 0); 
        glRotated(angZ, 0, 0, 1);

		if (e)
			escena->dibuja();
		if (c)
			coche->dibuja();
		if (t)
			toro->dibuja();
		if (p)
			prisma->dibuja();
		if (r)
			mallaRevolucion->dibuja();
		if (X)
			copa->dibuja();
			
	glPopMatrix();

	glFlush();
	glutSwapBuffers();
}


void resize(int newWidth, int newHeight) {
	WIDTH= newWidth;
	HEIGHT= newHeight;
	GLdouble RatioViewPort= (float)WIDTH/(float)HEIGHT;
	glViewport (0, 0, WIDTH, HEIGHT) ;
     
	GLdouble SVAWidth= xRight-xLeft;
	GLdouble SVAHeight= yTop-yBot;
	GLdouble SVARatio= SVAWidth/SVAHeight;
	if (SVARatio >= RatioViewPort) {		 
		GLdouble newHeight= SVAWidth/RatioViewPort;
		GLdouble yMiddle= ( yBot+yTop )/2.0;
		yTop= yMiddle + newHeight/2.0;
		yBot= yMiddle - newHeight/2.0;
    }
	else {      
		GLdouble newWidth= SVAHeight*RatioViewPort;
		GLdouble xMiddle= ( xLeft+xRight )/2.0;
		xRight= xMiddle + newWidth/2.0;
		xLeft=  xMiddle - newWidth/2.0;
	}
	
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();   
	//glFrustum(xLeft, xRight, yBot, yTop, N, F);
	glOrtho(xLeft, xRight, yBot, yTop, N, F);	
}

void key(unsigned char key, int x, int y){
	bool need_redisplay = true;
	switch (key) {
		case 27:  /* Escape key */
			//continue_in_main_loop = false; // (**)
			//Freeglut's sentence for stopping glut's main loop (*)
			glutLeaveMainLoop (); 
			break;					 
                case 'a': angX=(angX+5)%360; break;
				case 'z': angX=(angX-5)%360; break; 
				case 's': angY=(angY+5)%360; break;
				case 'x': angY=(angY-5)%360; break;
				case 'd': angZ=(angZ+5)%360; break;
				case 'c': angZ=(angZ-5)%360; break;                 
				case 'i': 					 
					glEnable(GL_LIGHT2);  					
					break;         
				case 'k': 					 										
					glDisable(GL_LIGHT2);
					break;
				case '+':
					{
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();   
						glOrtho (-1, 1, -1, 1, 1, 100);
					}
					break;
				case '-':
					{
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();   
						glOrtho(xLeft, xRight, yBot, yTop, N, F);
					}
					break;
				case 'E':
					{
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();   
						glOrtho(xLeft, xRight, yBot, yTop, N, F);
						e=true;
						c=false;
						t=false;
						p=false;
						r=false;
						X=false;
					}
					break;
				case 'C':
					{
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();   
						glOrtho(xLeft, xRight, yBot, yTop, N, F);
						e=false;
						c=true;
						t=false;
						p=false;
						r=false;
						X=false;
					}
					break;
				case 'T':
					{
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();   
						glOrtho (-1, 1, -1, 1, 1, 100);
						e=false;
						c=false;
						t=true;
						p=false;
						r=false;
						X=false;
					}
					break;
				case 'P':
					{
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();   
						glOrtho (-1, 1, -1, 1, 1, 100);
						e=false;
						c=false;
						t=false;
						p=true;
						r=false;
						X=false;
					}
					break;
				case 'R':
					{
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();   
						glOrtho (-1, 1, -1, 1, 1, 100);
						e=false;
						c=false;
						t=false;
						p=false;
						r=true;
						X=false;
					}
					break;
				case 'X':
					{
						glMatrixMode(GL_PROJECTION);
						glLoadIdentity();   
						glOrtho (-1, 1, -1, 1, 1, 100);
						e=false;
						c=false;
						t=false;
						p=false;
						r=false;
						X=true;
					}
					break;
		default:
			need_redisplay = false;
			break;
	}

	if (need_redisplay)
		glutPostRedisplay();
}

int main(int argc, char *argv[]){
	cout<< "Starting console..." << endl;

	int my_window; // my window's identifier

	// Initialization
	glutInitWindowSize(WIDTH, HEIGHT);
	glutInitWindowPosition (140, 140);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInit(&argc, argv);

	// Window construction
	my_window = glutCreateWindow("Freeglut 3D-project");
    
	// Callback registration
	glutReshapeFunc(resize);
	glutKeyboardFunc(key);
	glutDisplayFunc(display);

	// OpenGL basic setting
	initGL();

	// Freeglut's main loop can be stopped executing (**)
	// while (continue_in_main_loop) glutMainLoopEvent();

	// Classic glut's main loop can be stopped after X-closing the window,
	// using the following freeglut's setting (*)
	glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_CONTINUE_EXECUTION) ;
    
	// Classic glut's main loop can be stopped in freeglut using (*)
	glutMainLoop(); 
  
	// We would never reach this point using classic glut
	system("PAUSE"); 
   
	return 0;
}
