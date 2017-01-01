//===========================================
// Javier Martin Moreno-Manzanaro
//===========================================

#include "Coche.h"

Coche::Coche() {
	//creamos las ruedas y les ponemos color
	ruedas = new Rueda*[4];
	for (int i=0; i<4;i++) {
		ruedas[i] = new Rueda();
		ruedas[i]->setColor(1.0,1.0, 1.0);
	}
	//colocamos las ruedas
	ruedas[0]->traslada(new PuntoVector3D (-3.0, -3.0, -4.0, 1));
	ruedas[0]->rota(180, 1.0, 0.0, 0.0);
	ruedas[1]->traslada(new PuntoVector3D (-3.0, -3.0, 4.0, 1));
	ruedas[2]->traslada(new PuntoVector3D (3.0, -3.0, 4.0, 1));
	ruedas[3]->traslada(new PuntoVector3D (3.0, -3.0, -4.0, 1));
	ruedas[3]->rota(180, 1.0, 0.0, 0.0);

	//Creamos el chasis, ponemos color y lo aumentamos
	chasis = new Cubo();
	chasis->setColor(0.3, 0.7, 0.3);
	chasis->escala(15.0, 15.0, 15.0);

	//Creamos los faros, ponemos color, y los colocamos
	faros = new Cilindro*[2];
	faros[0] = new Cilindro(1.0, 0.001, 2.0, 20, 30);
	faros[0]->setColor(1.0, 1.0, 0.0);
	faros[0]->traslada(new PuntoVector3D(6.0, -1.0, -2.0, 1));
	faros[0]->rota(-90, 0.0, 1.0, 0.0);
	faros[1] = new Cilindro(1.0, 0.001, 2.0, 20, 30);
	faros[1]->setColor(1.0, 1.0, 0.0);
	faros[1]->traslada(new PuntoVector3D(6.0, -1.0, 2.0, 1));
	faros[1]->rota(-90, 0.0, 1.0, 0.0);
}

Coche::~Coche(){
	for (int i=0; i<4;i++)
		delete ruedas[i];
	delete []ruedas;
	delete chasis;
}

void Coche::dibuja(){
	glMatrixMode(GL_MODELVIEW); //Post-multiplicamos y dibujamos
	glPushMatrix();
		glMultMatrixf(matriz->dameMatrizModelado());
		//Pedimos color y pintamos las ruedas
		for (int i=0; i<4; i++){
			glColor3f(ruedas[i]->getColor()->getR(), ruedas[i]->getColor()->getG(), ruedas[i]->getColor()->getB());
			ruedas[i]->dibuja();
		}

		//pedimos color y pintamos el chasis
		glColor3f(chasis->getColor()->getR(), chasis->getColor()->getG(), chasis->getColor()->getB());
		chasis->dibuja();

		//pedimos el color y pintamos los faros
		for (int i=0; i<2; i++){
			glColor3f(faros[i]->getColor()->getR(), faros[i]->getColor()->getG(), faros[i]->getColor()->getB());
			faros[i]->dibuja();
		}
	glPopMatrix();
}