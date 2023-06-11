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
	/*
	std::cout << "Bienvenido al juego Batalla Digital V2.0!" << std::endl;

	std::cin.clear();
	std::cout << "Antes de comenzar a jugar, necesitamos que se ingrese la cantidad de jugadores que jugarán: ";

	int num = 0 ;

	std::cin >> num ;

	std::cout << "El numero ingresado es: " << num ;



	return 0 ;
	 */


	// Creo la clase del juego batalla digital
	BatallaDigital * batallaDigital = new BatallaDigital();
	//batallaDigital->mostrarTablero(NULL);

	// Una vez que genero el tablero se colocan las fichas al comienzo del juego
	batallaDigital->colocarFichasIniciales();;


	// Obtengo el primer jugador de la lista
	Jugador *jugadorTurnoActual = batallaDigital->obtenerPrimerJugador();

	int idJugadorTurno = jugadorTurnoActual->getIdentificador();
	int idJugadorTurnoAnterior = 0;

	while(!batallaDigital->hayGanador())
	{	

		//batallaDigital->mostrarTablero(jugadorTurnoActual);
		batallaDigital->avanzarTurno(jugadorTurnoActual);

		std::cout << "Avanzo turno " << std::endl;

		idJugadorTurnoAnterior = idJugadorTurno;
		jugadorTurnoActual = batallaDigital->obtenerSiguienteJugador(idJugadorTurnoAnterior);

		idJugadorTurno = jugadorTurnoActual->getIdentificador();
	}

	//Si hay ganador, notifico cuál es y termino el juego

	//batallaDigital->imprimirQuienGano();

	cout << "====..... Fin .....====" << endl;
	return 0;
}
