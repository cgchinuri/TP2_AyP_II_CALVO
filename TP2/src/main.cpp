//============================================================================
// Name        : Trabajo práctico número 2
// Author      : 
// Version     : 1.0
// Copyright   : Algoritmos II - Facultad de Ingeniería de la UBA
// Description : Batalla digital V2.0
//===========================================================================

#include <iostream>

#include "tablero.h"

using namespace std;

int main() {

	Tablero tablero_juego(4, 5, 6);

	cout << "tablero construido" << endl;

	tablero_juego.imprimirTablero();


	cout << "====..... Fin .....====" << endl;
	return 0;
}
