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
#include "Utils/TipoMovimiento.h"

using namespace std;

int main() 
{
	cout << "Inicio" << endl;


	// Creo la clase del juego batalla digital
	BatallaDigital * batallaDigital = new BatallaDigital();


	/* 
	------------------------------------ PRUEBAS 30/05 ------------------------------------
	Esto es para chequear que se detecte si hay algun jugador sin fichas de soldados
	Ficha * fichaAux = NULL;
	fichaAux = batallaDigital->crearFicha(FICHA_SOLDADO, 4,5,4,1);
	if(batallaDigital->hayGanador()!=true)
	{	
		cout << "====..... Hay jugadores en pie .....====" << endl;
	}




	Esto es para saber cómo se está generando el terreno del tablero
	*/
	

	//batallaDigital->mostrarGeografiaTablero();


	/*
	// ------------------------------------ PRUEBAS 28/05 ------------------------------------
	// Variables auxiliares
	Ficha * fichaAux = NULL;
	Casillero * casilleroAux = NULL;
	Coordenada<int>  * coordenadaAux = NULL;

	// Creo una ficha y la enlazo a un casillero
	fichaAux = batallaDigital->crearFicha(FICHA_SOLDADO, 4,5,4);
	// Tomo el casillero enlazado a la ficha
	casilleroAux = fichaAux->getCasilleroFicha();
	// Tomo la coordenada del casillero enlazado a la ficha
	coordenadaAux = casilleroAux->getCoordenada();
	// Me fijo que todo coincida
	cout << "Casillero sobre el cual se puso la ficha: " << coordenadaAux->toString() << endl;

	// Me fijo que el casilleroe esté ocupado, si no está mal
	if(casilleroAux->estaOcupado())
	{
		cout << "Casillero ocupado OK" << endl;
	}
	else
	{
		cout << "Casillero desocupado ERROR" << endl;
	}

	// Ahora voy a mover la ficha
	batallaDigital->moverFicha(fichaAux, adelante_izquierda ,  3);

	// Guardo los datos del casillero anterior
	Casillero * casilleroViejoAux = casilleroAux;

	// Repito las verificaciones
	// Tomo el casillero enlazado a la ficha
	casilleroAux = fichaAux->getCasilleroFicha();

	// Tomo la coordenada del casillero enlazado a la ficha
	coordenadaAux = casilleroAux->getCoordenada();

	// Me fijo que todo coincida
	cout << "Casillero al cual se movió la ficha: " << coordenadaAux->toString() << endl;

	// Me fijo que el casilleroe esté ocupado, si no está mal
	if(casilleroAux->estaOcupado())
	{
		cout << "Casillero nuevo ocupado OK" << endl;
	}
	else
	{
		cout << "Casillero nuevo desocupado ERROR" << endl;
	}

	if(casilleroViejoAux->estaOcupado())
	{
		cout << "Casillero viejo ocupado ERROR" << endl;
	}
	else
	{
		cout << "Casillero viejo desocupado OK" << endl;
	}
	// ------------------------------ FIN PRUEBAS 28/05 ------------------------------------
	 */



	// Una vez que genero el tablero se colocan las fichas al comienzo del juego
	batallaDigital->colocarFichasIniciales();

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
