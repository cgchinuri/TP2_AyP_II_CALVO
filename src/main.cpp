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
	BatallaDigital * batallaDigital = new BatallaDigital();
	batallaDigital->mostrarTablero(NULL);

	// Una vez que genero el tablero se colocan las fichas al comienzo del juego
	batallaDigital->colocarFichasIniciales();;

	// Una vez colocadas las fichas de todos los jugadores procedemos al ciclo del juego
	unsigned int turno = 1;
	while(batallaDigital->hayGanador()==false)
	{	
		std::cout<<std::endl;
		std::cout<<"Nuevo turno"<<std::endl;
		Jugador *jugadorTurnoActual = batallaDigital->obtenerJugadorNumero(turno);
		batallaDigital->mostrarTablero(jugadorTurnoActual);
		batallaDigital->avanzarTurno(jugadorTurnoActual);
	}

	//Si hay ganador, notifico cuál es y termino el juego

	//batallaDigital->imprimirQuienGano();

	cout << "====..... Fin .....====" << endl;
	return 0;
}
