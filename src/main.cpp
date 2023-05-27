//============================================================================
// Name        : Trabajo práctico número 2
// Author      : 
// Version     : 1.0
// Copyright   : Algoritmos II - Facultad de Ingeniería de la UBA
// Description : Batalla digital V2.0
//===========================================================================

#include <iostream>

#include "Tablero/tablero.h"
#include "Jugador/Jugador.h"
#include "BatallaDigital/BatallaDigital.h"

using namespace std;

int main() 
{
	cout << "Inicio" << endl;


	// Creo la clase del juego batalla digital
	BatallaDigital * batallaDigital = NULL;

	batallaDigital = new BatallaDigital();

	// Una vez que genero el tablero se colocan las fichas al comienzo del juego
	// colocarFichasIniciales();

	// Una vez colocadas las fichas de todos los jugadores procedemos al ciclo del juego
	/* while(hayGanador!=false)
	{	
		jugadorTomaCarta();
		jugadorMueveFicha();
		//opcional jugadorUsaCarta();
		siguienteTurno();
	}
	*/

	cout << "====..... Fin .....====" << endl;
	return 0;
}