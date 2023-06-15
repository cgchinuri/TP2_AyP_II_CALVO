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
	// Creo la clase del juego batalla digital
	BatallaDigital * batallaDigital = new BatallaDigital();

	batallaDigital->mostrarTablero(NULL);

	// Una vez que genero el tablero se colocan las fichas al comienzo del juego
	batallaDigital->colocarFichasIniciales();;


	// Obtengo el primer jugador de la lista
	Jugador *jugadorTurnoActual = batallaDigital->obtenerPrimerJugador();

	// Creo el puntero al jugador que será el ganador del juego
	Jugador *jugadorGanador = NULL;

	// Variables para gestionar los turnos de los jugadores
	int idJugadorTurno = jugadorTurnoActual->getIdentificador();
	int idJugadorTurnoAnterior = 0;

	// Ciclo del juego
	// Se jugará hasta que haya un ganador
	while(!batallaDigital->hayGanador(&jugadorGanador))
	{	
		batallaDigital->mostrarTablero(jugadorTurnoActual);

		// Turno del jugador actual
		batallaDigital->avanzarTurno(jugadorTurnoActual);

		// Almaceno el ID del jugador actual como anterior
		idJugadorTurnoAnterior = idJugadorTurno;

		// Guardo en el puntero a jugador el jugador que va a jugar el próximo turno
		jugadorTurnoActual = batallaDigital->obtenerSiguienteJugador(idJugadorTurnoAnterior);

		// Guardo el ID en la variable
		idJugadorTurno = jugadorTurnoActual->getIdentificador();
	}

	//Si hay ganador, notifico cuál es y termino el juego
	batallaDigital->imprimirGanador(jugadorGanador);

	cout << "====..... Fin .....====" << endl;
	return 0;
}
