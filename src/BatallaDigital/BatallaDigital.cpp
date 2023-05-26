#include "BatallaDigital.h"


//Clase juego



BatallaDigital::BatallaDigital(unsigned int cantJugadores, unsigned int * dimTab)
{
	// 1 generacion del tablero

	// 2 generacion de lista de jugadores
}


void BatallaDigital::vincularFichaYCasillero(Casillero * casillero , Ficha * ficha)
{
	casillero->setFichaCasillero(ficha);
	ficha->setCasilleroFicha(casillero);
}

void BatallaDigital::desvincularFicha(Ficha * ficha)
{
	ficha->desvincularFichaDeCasillero();
}


void desvincularCasillero(Casillero * casillero)
{
	casillero->vaciarCasillero();
}