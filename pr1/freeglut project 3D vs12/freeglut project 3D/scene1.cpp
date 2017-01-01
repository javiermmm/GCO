//---------------------------------------------------------------------------
#include "scene1.h"
//---------------------------------------------------------------------------

scene::scene(){
  estrella.pEsf=gluNewQuadric();
  planeta.pEsf = gluNewQuadric();
  satelite.pEsf = gluNewQuadric();
  orbitaP = gluNewQuadric();
  orbitaS = gluNewQuadric();
  orbitaSputnik = gluNewQuadric();
  iniciar();
}

scene::~scene(){
  gluDeleteQuadric(estrella.pEsf);
  gluDeleteQuadric(planeta.pEsf);
  gluDeleteQuadric(satelite.pEsf);
  gluDeleteQuadric(orbitaP);
  gluDeleteQuadric(orbitaS);
  gluDeleteQuadric(orbitaSputnik);
}

void scene::iniciar(){

	//Light1 set up luz interna del Sol
	glEnable(GL_LIGHT1);
	GLfloat LuzDifusa1[4] = { 1.0, 1.0, 1.0, 1.0 }; //color blanco
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LuzDifusa1);

	//Preparacion de la estrella
	estrella.ang=0;
	estrella.dis=0;
	gluQuadricDrawStyle(estrella.pEsf, GLU_FILL);  //  GLU_LINE
	gluQuadricOrientation (estrella.pEsf,GLU_OUTSIDE); // GLU_INSIDE 
	gluQuadricNormals(estrella.pEsf,GLU_SMOOTH);  // GLU_FLAT

	//Preparacion del planeta
	planeta.ang = 0;
	planeta.dis = 103;
	gluQuadricDrawStyle(planeta.pEsf, GLU_FILL);  //  GLU_LINE
	gluQuadricOrientation(planeta.pEsf, GLU_OUTSIDE); // GLU_INSIDE 
	gluQuadricNormals(planeta.pEsf, GLU_SMOOTH);  // GLU_FLAT

	//Preparacion del satelite
	satelite.ang = 0;
	satelite.dis = 49;
	gluQuadricDrawStyle(satelite.pEsf, GLU_FILL);  //  GLU_LINE
	gluQuadricOrientation(satelite.pEsf, GLU_OUTSIDE); // GLU_INSIDE 
	gluQuadricNormals(satelite.pEsf, GLU_SMOOTH);  // GLU_FLAT

	//Preparación del satélite artificial
	sputnik.ang = 0;
	sputnik.dis = 34;

	
	//iniciamos las tablas de la malla
	sateliteArtificial.tablaVertices[0] = { 0, 0, 0, {0.0, 1.0, 0.0} };
	sateliteArtificial.tablaVertices[1] = { 0, 1, 1, {1.0, 0.0, 0.0} };
	sateliteArtificial.tablaVertices[2] = { -1, 1, 0, {0.0, 0.0, 1.0} };
	sateliteArtificial.tablaVertices[3] = { 0, 1, -1, {1.0, 0.0, 0.0} };
	sateliteArtificial.tablaVertices[4] = { 1, 1, 0, {0.0, 0.0, 1.0} };
	sateliteArtificial.tablaVertices[5] = { -1, -1, 0, {0.0, 0.0, 1.0} };
	sateliteArtificial.tablaVertices[6] = { 0, -1, 1, {1.0, 0.0, 0.0} };
	sateliteArtificial.tablaVertices[7] = { 0, -1, -1, {1.0, 0.0, 0.0} };
	sateliteArtificial.tablaVertices[8] = { 1, -1, 0, {0.0, 0.0, 1.0} };
	
	sateliteArtificial.tablaNormales[0] = { 0.577, -0.577, 0.577};
	sateliteArtificial.tablaNormales[1] = {-0.577, -0.577, 0.577};
	sateliteArtificial.tablaNormales[2] = {-0.577, -0.577, -0.577};
	sateliteArtificial.tablaNormales[3] = {0.577, -0.577, -0.577};
	sateliteArtificial.tablaNormales[4] = {0.577, 0.577, 0.577};
	sateliteArtificial.tablaNormales[5] = {-0.577, 0.577, 0.577};
	sateliteArtificial.tablaNormales[6] = {-0.577, 0.577, -0.577};
	sateliteArtificial.tablaNormales[7] = {0.577, 0.577, -0.577};

	sateliteArtificial.tablaCaras[0] = { 3, {4, 1, 0}, {0, 0, 0} };
	sateliteArtificial.tablaCaras[1] = { 3, {1, 2, 0}, {1, 1, 1} };
	sateliteArtificial.tablaCaras[2] = { 3, {2, 3, 0}, {2, 2, 2} };
	sateliteArtificial.tablaCaras[3] = { 3, {3, 4, 0}, {3, 3, 3} };
	sateliteArtificial.tablaCaras[4] = { 3, {0, 6, 8}, {4, 4, 4} };
	sateliteArtificial.tablaCaras[5] = { 3, {0, 5, 6}, {5, 5, 5} };
	sateliteArtificial.tablaCaras[6] = { 3, {0, 7, 5}, {6, 6, 6} };
	sateliteArtificial.tablaCaras[7] = { 3, {0, 8, 7}, {7, 7, 7} };
}

void scene::dibujaEjes() {
	// Drawing axes
	glBegin(GL_LINES);
	glColor3f(1.0, 0.0, 0.0); // red
	glVertex3f(0, 0, 0);      // origin
	glVertex3f(200, 0, 0);	  // x   

	glColor3f(0.0, 1.0, 0.0); // green
	glVertex3f(0, 0, 0);      // center
	glVertex3f(0, 200, 0);	  // y

	glColor3f(0.0, 0.0, 1.0); // blue
	glVertex3f(0, 0, 0);      // origin
	glVertex3f(0, 0, 200);	  // z   
	glEnd();
}

void scene::triangulo() {
	glBegin(GL_TRIANGLES);  // triángulo: secuencia de tuplas
		glNormal3f(1.0, 1.0, 1.0);  // normal xyz. Vector normal
		glColor3f(1.0, 0.0, 0.0);   // red
		glVertex3f(1.0, 0.0, 0.0);  // vértice x
		glColor3f(0.0, 1.0, 0.0);   // green
		glVertex3f(0.0, 1.0, 0.0);  // vértice y
		glColor3f(0.0, 0.0, 1.0);   // blue
		glVertex3f(0.0, 0.0, 1.0);  // vértice z
	glEnd();
}

void scene::piramide() {
	for (int i = 0; i<4; i++) {
		triangulo();
		glRotated(90.0, 0.0, 1.0, 0.0);
	}
}

void scene::drawSateliteArtificial() {
	glPushMatrix();
	glRotated(sputnik.ang, 0.0, 0.0, 1.0);
	glTranslated(sputnik.dis, 0.0, 0.0);
	glScaled(6, 6, 6);
	for (int i=0; i<8; i++) { //Para cada cara
		glBegin(GL_TRIANGLES);
			for (int j=0; j<sateliteArtificial.tablaCaras[i].numVertices; j++) { //Para cada vertice de la cara
				glNormal3f(sateliteArtificial.tablaNormales[sateliteArtificial.tablaCaras[i].indNormales[j]].x, sateliteArtificial.tablaNormales[sateliteArtificial.tablaCaras[i].indNormales[j]].y, sateliteArtificial.tablaNormales[sateliteArtificial.tablaCaras[i].indNormales[j]].z);
				glColor3f(sateliteArtificial.tablaVertices[sateliteArtificial.tablaCaras[i].indVertices[j]].color.R, sateliteArtificial.tablaVertices[sateliteArtificial.tablaCaras[i].indVertices[j]].color.G, sateliteArtificial.tablaVertices[sateliteArtificial.tablaCaras[i].indVertices[j]].color.B);
				glVertex3f(sateliteArtificial.tablaVertices[sateliteArtificial.tablaCaras[i].indVertices[j]].x, sateliteArtificial.tablaVertices[sateliteArtificial.tablaCaras[i].indVertices[j]].y, sateliteArtificial.tablaVertices[sateliteArtificial.tablaCaras[i].indVertices[j]].z);
			}
		glEnd();
	}
	glPopMatrix();
}


void scene::drawSputnik() {
	glPushMatrix();
	glRotated(sputnik.ang, 0.0, 0.0, 1.0);
	glTranslated(sputnik.dis, 0.0, 0.0);
	glScaled(6, 6, 6);
	//Pintamos la primera piramide
	glTranslated(0.0, -1.0, 0.0);
	piramide();
	//Pintamos la segunda piramide
	glScaled(1.0, -1.0, 1.0); //Con esto giramos la piramide, es decir, escalamos con valor negativo
	glTranslated(0.0, -2.0, 0.0);
	piramide();
	glPopMatrix();
}

void scene::drawOrbitaP() {
	glPushMatrix();
	glColor4f(0.0, 1.0, 1.0, 1.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	gluDisk(orbitaP, planeta.dis, planeta.dis +5, 30, 1);
	glPopMatrix();
}

void scene::drawOrbitaS() {
	glPushMatrix();
	glColor4f(1.0, 0.0, 0.0, 1.0);
	glRotated(90.0, 1.0, 0.0, 0.0);
	gluDisk(orbitaS, satelite.dis, satelite.dis + 5, 30, 1);
	glPopMatrix();
}


void scene::drawOrbitaSputnik() {
	glColor4f(0.7, 0.0, 0.7, 1.0);
	gluDisk(orbitaSputnik, sputnik.dis, sputnik.dis + 2, 30, 1);
}

void scene::drawEstrella(){
  glPushMatrix();
    glColor4f(1.0,1.0,0.0,1.0);
	
	//decimos que los objetos emitan luz
	GLfloat luzAmarilla[4] = { 0.5, 0.5, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, luzAmarilla);
	
	//colocamos el sol
    glRotated(estrella.ang,0,1,0);   // Y-roll
    glTranslated(estrella.dis,0,0);  // en el eje X

	//posicionamos la luz fuerte, del sol
	GLfloat posLuz1[4] = { 0.0, 0.0, 0.0, 1.0 };
	glLightfv(GL_LIGHT1, GL_POSITION, posLuz1);
    gluSphere(estrella.pEsf,45,24,24);

	//Desactivamos la emision de luz de los objetos
	GLfloat sinColor[4] = { 0.0, 0.0, 0.0, 1.0 };
	glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, sinColor);

	drawOrbitaP();
	drawPlaneta();
  glPopMatrix();
}

void scene::drawPlaneta() {
	glPushMatrix();
	glColor4f(0.0, 0.0, 1.0, 1.0);
	glRotated(planeta.ang, 0, 1, 0);   // Y-roll
	glTranslated(planeta.dis, 0, 0);  // en el eje X
	gluSphere(planeta.pEsf, 27, 24, 24);
	drawOrbitaS();
	drawSatelite();
	drawOrbitaSputnik();
	//drawSputnik();
	drawSateliteArtificial();
	glPopMatrix();
}

void scene::drawSatelite() {
	glPushMatrix();
	glColor4f(1.0, 1.0, 1.0, 1.0);
	glRotated(satelite.ang, 0, 1, 0);   // Y-roll
	glTranslated(satelite.dis, 0, 0);  // en el eje X
	gluSphere(satelite.pEsf, 8, 24, 24);
	glPopMatrix();
}

void scene::dibujar(){
	glMatrixMode(GL_MODELVIEW);
	
	dibujaEjes();
	drawEstrella();
	//drawOrbitaP();
}

void scene::incAngEstrella(GLint a){
  estrella.ang = (estrella.ang + a) % 360;
}

void scene::incAngPlaneta(GLint a){
	planeta.ang = (planeta.ang + a) % 360;
}

void scene::incAngSatelite(GLint a){
	satelite.ang = (satelite.ang + a) % 360;
}

void scene::incAngSputnik(GLint a){
	sputnik.ang = (sputnik.ang + a) % 360;
}

void scene::setDisEstrella(GLdouble d){
  estrella.dis = d;  
}

