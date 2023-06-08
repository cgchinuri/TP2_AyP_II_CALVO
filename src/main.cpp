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
/*	Tablero *tablero = new Tablero(10, 10, 10);
	struct Imagenes *imagenes = new struct Imagenes;
	iniciarBitmap(5,5,imagenes);
	dibujarTablero(tablero, imagenes);
	delete imagenes;
	delete tablero;
*/

	// ↑ ESTE main así no tiene errores de memoria
	cout << "Inicio" << endl;


	// Creo la clase del juego batalla digital
	BatallaDigital * batallaDigital = new BatallaDigital();


	// Una vez que genero el tablero se colocan las fichas al comienzo del juego
	batallaDigital->colocarFichasIniciales();

	// Una vez colocadas las fichas de todos los jugadores procedemos al ciclo del juego
	batallaDigital->mostrarTablero(0);

	// Una vez colocadas las fichas de todos los jugadores procedemos al ciclo del juego
	unsigned int turno=1;
	while(batallaDigital->hayGanador()==false)
	{	
		batallaDigital->avanzarTurno(batallaDigital->obtenerJugadorNumero(turno));
		if (turno==batallaDigital->cantidadDeJugadores())
		{
			turno=1;
		}
		else
		{
			turno++;
		}
	}

	//Si hay ganador, notifico cuál es y termino el juego

	//batallaDigital->imprimirQuienGano();

	cout << "====..... Fin .....====" << endl;
	return 0;
}
