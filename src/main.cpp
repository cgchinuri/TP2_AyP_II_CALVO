//============================================================================
// Name        : Trabajo práctico número 2
// Author      : 
// Version     : 1.0
// Copyright   : Algoritmos II - Facultad de Ingeniería de la UBA
// Description : Batalla digital V2.0
//===========================================================================

#include <iostream>

#include "tablero.h"
#include "Ficha.hpp"
#include "BatallaDigital/BatallaDigital.h"

using namespace std;

int main() {

	//unsigned int [3] dimensiones = {5,3,8};

	//BatallaDigital batallaDigital(3, dimensiones);

	cout << "Inicio" << endl;

	Tablero tableroJuego(5, 5, 5);
	
	cout << "tablero construido" << endl;

	tableroJuego.imprimirTablero();

	Casillero * auxCasilleroPtr = NULL;

	Ficha ficha1(FICHA_BARCO);
	ficha1.setCasilleroFicha( tableroJuego.obtenerCasillero(3,3,3) ) ;
	tableroJuego.obtenerCasillero(3,3,3)->setFichaCasillero(&ficha1);

	Ficha ficha2(FICHA_AVION);
	ficha2.setCasilleroFicha( tableroJuego.obtenerCasillero(4,4,4) ) ;
	tableroJuego.obtenerCasillero(4,4,4)->setFichaCasillero(&ficha2);

	Ficha ficha3(FICHA_SOLDADO);
	ficha3.setCasilleroFicha( tableroJuego.obtenerCasillero(1,2,3) ) ;
	tableroJuego.obtenerCasillero(1,2,3)->setFichaCasillero(&ficha3);

	Ficha ficha4(FICHA_MINA);
	ficha4.setCasilleroFicha( tableroJuego.obtenerCasillero(2,2,2) ) ;
	tableroJuego.obtenerCasillero(2,2,2)->setFichaCasillero(&ficha4);

	auxCasilleroPtr = ficha1.getCasilleroFicha();
	ficha1.imprimirInfo();
	cout << "Apunto al casillero: (" << auxCasilleroPtr->getPosX() << ", " << auxCasilleroPtr->getPosY() << ", " << auxCasilleroPtr->getPosZ() << ")" << endl;

	auxCasilleroPtr = ficha2.getCasilleroFicha();
	ficha2.imprimirInfo();
	cout << "Apunto al casillero: (" << auxCasilleroPtr->getPosX() << ", " << auxCasilleroPtr->getPosY() << ", " << auxCasilleroPtr->getPosZ() << ")" << endl;

	auxCasilleroPtr = ficha3.getCasilleroFicha();
	ficha3.imprimirInfo();
	cout << "Apunto al casillero: (" << auxCasilleroPtr->getPosX() << ", " << auxCasilleroPtr->getPosY() << ", " << auxCasilleroPtr->getPosZ() << ")" << endl;

	auxCasilleroPtr = ficha4.getCasilleroFicha();
	ficha4.imprimirInfo();
	cout << "Apunto al casillero: (" << auxCasilleroPtr->getPosX() << ", " << auxCasilleroPtr->getPosY() << ", " << auxCasilleroPtr->getPosZ() << ")" << endl;


	cout << "====..... Fin .....====" << endl;
	return 0;
}
